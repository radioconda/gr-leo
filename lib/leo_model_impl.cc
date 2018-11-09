/* -*- c++ -*- */
/*
 * gr-leo: SatNOGS GNU Radio Out-Of-Tree Module
 *
 *  Copyright (C) 2018, Libre Space Foundation <https://libre.space/>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "leo_model_impl.h"
#include <cstring>
#include <leo/free_space_path_loss.h>
#include <leo/atmospheric_gases_itu.h>
#include <leo/atmospheric_gases_regression.h>
#include <leo/precipitation_itu.h>
#include <leo/utils/helper.h>
#include <leo/log.h>
#include <volk/volk.h>

namespace gr
{
  namespace leo
  {
    namespace model
    {

      generic_model::generic_model_sptr
      leo_model::make (tracker::tracker_sptr tracker, const uint8_t mode,
                       const uint8_t atmo_gases_attenuation,
                       const uint8_t precipitation_attenuation,
                       const float surface_watervap_density,
                       const float temperature, const float rainfall_rate)
      {
        return generic_model::generic_model_sptr (
            new leo_model_impl (tracker, mode, atmo_gases_attenuation,
                                precipitation_attenuation,
                                surface_watervap_density, temperature,
                                rainfall_rate));
      }

      leo_model_impl::leo_model_impl (tracker::tracker_sptr tracker,
                                      const uint8_t mode,
                                      const uint8_t atmo_gases_enum,
                                      const uint8_t precipitation_enum,
                                      const float surface_watervap_density,
                                      const float temperature,
                                      const float rainfall_rate) :
              generic_model ("leo_model", tracker, mode),
              d_nco (),
              d_slant_range (0),
              d_doppler_shift (0),
              d_atmo_gases_enum ((atmo_gases_attenuation_t) atmo_gases_enum),
              d_surface_watervap_density (surface_watervap_density),
              d_temperature (temperature),
              d_rainfall_rate (rainfall_rate),
              d_write_csv_header (true),
              d_atmo_attenuation (0),
              d_rainfall_attenuation (0),
              d_pathloss_attenuation (0)
      {
        d_nco.set_freq (0);

        orbit_update ();

        switch (atmo_gases_enum)
          {
          case ATMO_GASES_ITU:
            d_atmo_gases_attenuation =
                attenuation::atmospheric_gases_itu::make (
                    d_surface_watervap_density);
            break;
          case ATMO_GASES_REGRESSION:
            d_atmo_gases_attenuation =
                attenuation::atmospheric_gases_regression::make (
                    d_surface_watervap_density, d_temperature);
            break;
          case ATMO_GASES_NONE:
            break;
          default:
            throw std::runtime_error ("Invalid atmospheric gases attenuation!");
          }

        switch (precipitation_enum)
          {
          case PRECIPITATION_ITU:
          case PRECIPITATION_CUSTOM:
            d_precipitation_attenuation = attenuation::precipitation_itu::make (
                d_rainfall_rate, d_tracker->get_lontitude (),
                d_tracker->get_latitude (), d_tracker->get_altitude (),
                (precipitation_attenuation_t) precipitation_enum);
            break;
          case PRECIPITATION_NONE:
            break;
          default:
            throw std::runtime_error ("Invalid precipitation attenuation!");
          }

        d_fspl_attenuation = attenuation::free_space_path_loss::make (
            get_tracker_antenna_gain (), get_satellite_antenna_gain ());

      }

      leo_model_impl::~leo_model_impl ()
      {
      }

      float
      leo_model_impl::calculate_doppler_shift (double velocity)
      {
        return (1e3 * velocity * get_frequency ()) / LIGHT_SPEED;
      }

      float
      leo_model_impl::calculate_total_attenuation ()
      {
        float total_attenuation = 0;

        orbit_update ();

        if (d_atmo_gases_attenuation) {
          d_atmo_attenuation = d_atmo_gases_attenuation->get_attenuation ();
          total_attenuation += d_atmo_attenuation;
        }
        if (d_precipitation_attenuation) {
          d_rainfall_attenuation =
              d_precipitation_attenuation->get_attenuation ();
          total_attenuation += d_rainfall_attenuation;
        }
        if (d_fspl_attenuation) {
          d_pathloss_attenuation = d_fspl_attenuation->get_attenuation ();
          total_attenuation += d_pathloss_attenuation;
        }

        generate_csv_log();

        LEO_DEBUG(
            "Time: %s | Slant Range (km): %f | Elevation (degrees): %f | Path Loss (dB): %f | Atmospheric Loss (dB): %f | Rainfall Loss (dB): %f | Doppler (Hz): %f",
            d_tracker->get_elapsed_time ().ToString ().c_str (), d_slant_range,
            d_tracker->get_elevation_degrees (), d_pathloss_attenuation,
            d_atmo_attenuation, d_rainfall_attenuation, d_doppler_shift);

        return total_attenuation;
      }

      void
      leo_model_impl::generate_csv_log ()
      {
        std::ostringstream stringStream;
        if (d_write_csv_header) {
          stringStream << "Elapsed Time (us)" << "," << "Slant Range (km)"
              << "," << "Elevation (degrees)" << "," << "Path Loss (dB)" << ","
              << "Atmospheric Loss (dB)" << "," << "Rainfall Loss (dB)" << ","
              << "Doppler Shift (Hz)";
          d_write_csv_header = false;
        }
        else {
          stringStream << d_tracker->get_elapsed_time ().ToString ().c_str ()
              << "," << d_slant_range << ","
              << d_tracker->get_elevation_degrees () << ","
              << d_pathloss_attenuation << "," << d_atmo_attenuation << ","
              << d_rainfall_attenuation << "," << d_doppler_shift;
        }
        d_csv_log = stringStream.str ();
      }

      void
      leo_model_impl::generic_work (const gr_complex *inbuffer,
                                    gr_complex *outbuffer, int noutput_items)
      {
        const gr_complex *in = (const gr_complex *) inbuffer;
        gr_complex *out = (gr_complex *) outbuffer;

        /**
         * TODO: Allocate a large enough vector at the constructor
         */
        gr_complex* tmp = new gr_complex[noutput_items];

        float pl_attenuation_db;
        float total_attenuation_db;
        float tracker_antenna_gain_db;
        float satellite_antenna_gain_db;

        gr_complex attenuation_linear;

        d_tracker->add_elapsed_time ();
        d_slant_range = d_tracker->get_slant_range ();

        if (d_slant_range) {
          d_doppler_shift = calculate_doppler_shift (
              d_tracker->get_velocity ());

          d_nco.set_freq (
              2 * M_PI * d_doppler_shift
                  / ((1e6 * noutput_items)
                      / d_tracker->get_time_resolution_us ()));
          d_nco.sincos (tmp, noutput_items, 1.0);
          volk_32fc_x2_multiply_32fc (tmp, tmp, inbuffer, noutput_items);

          /**
           * Get total attenuation in dB, convert it to linear and
           * multiply
           * TODO: Examine if restriction for elevation > 1 degree
           * should be set.
           */
          total_attenuation_db = calculate_total_attenuation ();
          attenuation_linear = gr_complex (
              1.0 / pow (10, (total_attenuation_db / 20)));
          volk_32fc_s32fc_multiply_32fc (outbuffer, tmp, attenuation_linear,
                                         noutput_items);
        }
        else {
          memset (outbuffer, 0, noutput_items * sizeof(gr_complex));
        }

        delete tmp;

      }
    } /* namespace model */
  } /* namespace leo */
} /* namespace gr */

