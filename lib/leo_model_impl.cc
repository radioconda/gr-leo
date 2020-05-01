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
#include <leo/antenna_pointing_loss.h>
#include <leo/utils/helper.h>
#include <leo/log.h>
#include <volk/volk.h>

namespace gr {
namespace leo {
namespace model {

generic_model::generic_model_sptr
leo_model::make(tracker::tracker_sptr tracker, const uint8_t mode,
                const uint8_t fspl_attenuation_enum,
                const uint8_t pointing_attenuation_enum,
                const uint8_t doppler_shift_enum,
                const uint8_t atmo_gases_attenuation,
                const uint8_t precipitation_attenuation,
                const uint8_t enable_link_margin,
                const float surface_watervap_density,
                const float temperature, const float rainfall_rate)
{
  return generic_model::generic_model_sptr(
           new leo_model_impl(tracker, mode, fspl_attenuation_enum,
                              pointing_attenuation_enum, doppler_shift_enum,
                              atmo_gases_attenuation,
                              precipitation_attenuation,
                              enable_link_margin,
                              surface_watervap_density, temperature,
                              rainfall_rate));
}

leo_model_impl::leo_model_impl(tracker::tracker_sptr tracker,
                               const uint8_t mode,
                               const uint8_t fspl_attenuation_enum,
                               const uint8_t pointing_attenuation_enum,
                               const uint8_t doppler_shift_enum,
                               const uint8_t atmo_gases_enum,
                               const uint8_t precipitation_enum,
                               const uint8_t enable_link_margin,
                               const float surface_watervap_density,
                               const float temperature,
                               const float rainfall_rate) :
  generic_model("leo_model", tracker, mode),
  d_doppler_shift_enum((const impairment_enum_t) doppler_shift_enum),
  d_doppler_shift(0),
  d_phase(1.0, 0.0),
  d_atmo_attenuation(0.0),
  d_rainfall_attenuation(0.0),
  d_pathloss_attenuation(0.0),
  d_pointing_attenuation(0.0),
  d_total_attenuation(0.0),
  d_slant_range(0.0),
  d_elev(0.0),
  d_surface_watervap_density(surface_watervap_density),
  d_temperature(temperature),
  d_rainfall_rate(rainfall_rate),
  d_write_csv_header(true),
  d_atmo_gases_attenuation(nullptr),
  d_precipitation_attenuation(nullptr),
  d_fspl_attenuation(nullptr),
  d_pointing_loss_attenuation(nullptr)
{
  orbit_update();

  switch (d_doppler_shift_enum) {
  case DOPPLER_SHIFT:
  case IMPAIRMENT_NONE:
    break;
  default:
    throw std::runtime_error("Invalid Doppler shift enumeration!");
  }

  switch (enable_link_margin) {
  case true:
    d_link_margin = link_margin::make();
    d_link_margin_db = std::numeric_limits<double>::infinity();
    break;
  case false:
    break;
  default:
    throw std::runtime_error("Invalid atmospheric gases attenuation!");
  }

  switch (atmo_gases_enum) {
  case ATMO_GASES_ITU:
    d_atmo_gases_attenuation =
      attenuation::atmospheric_gases_itu::make(
        d_surface_watervap_density);
    break;
  case ATMO_GASES_REGRESSION:
    d_atmo_gases_attenuation =
      attenuation::atmospheric_gases_regression::make(
        d_surface_watervap_density, d_temperature);
    break;
  case IMPAIRMENT_NONE:
    break;
  default:
    throw std::runtime_error("Invalid atmospheric gases attenuation!");
  }

  switch (precipitation_enum) {
  case PRECIPITATION_ITU:
  case PRECIPITATION_CUSTOM:
    d_precipitation_attenuation = attenuation::precipitation_itu::make(
                                    d_rainfall_rate, d_tracker->get_lontitude(),
                                    d_tracker->get_latitude(), d_tracker->get_altitude(),
                                    (impairment_enum_t) precipitation_enum);
    break;
  case IMPAIRMENT_NONE:
    break;
  default:
    throw std::runtime_error("Invalid precipitation attenuation!");
  }

  switch (fspl_attenuation_enum) {
  case FREE_SPACE_PATH_LOSS:
    d_fspl_attenuation = attenuation::free_space_path_loss::make();
    break;
  case IMPAIRMENT_NONE:
    break;
  default:
    throw std::runtime_error(
      "Invalid free-space path loss enumeration!");
  }

  switch (pointing_attenuation_enum) {
  case ANTENNA_POINTING_LOSS:
    d_pointing_loss_attenuation =
      attenuation::antenna_pointing_loss::make(
        get_tracker_antenna(), get_satellite_antenna());
    break;
  case IMPAIRMENT_NONE:
    break;
  default:
    throw std::runtime_error(
      "Invalid antenna pointing loss enumeration!");
  }
}

leo_model_impl::~leo_model_impl()
{
}

float
leo_model_impl::calculate_doppler_shift(double velocity)
{
  return (-1e3 * velocity * get_frequency()) / LIGHT_SPEED;
}

float
leo_model_impl::calculate_total_attenuation()
{
  d_total_attenuation = 0;

  orbit_update();

  if (d_atmo_gases_attenuation) {
    d_atmo_attenuation = d_atmo_gases_attenuation->get_attenuation();
    d_total_attenuation += d_atmo_attenuation;
  }
  if (d_precipitation_attenuation) {
    d_rainfall_attenuation =
      d_precipitation_attenuation->get_attenuation();
    d_total_attenuation += d_rainfall_attenuation;
  }
  if (d_fspl_attenuation) {
    d_pathloss_attenuation = d_fspl_attenuation->get_attenuation();
    d_total_attenuation += d_pathloss_attenuation;
  }
  if (d_pointing_loss_attenuation) {
    d_pointing_attenuation =
      d_pointing_loss_attenuation->get_attenuation();
    d_total_attenuation += d_pointing_attenuation;
  }
  if (d_link_margin) {
    estimate_link_margin();
  }

  generate_csv_log();

  LEO_DEBUG(
    "Time: %s | Slant Range (km): %f | Elevation (degrees): %f | \
    Path Loss (dB): %f | Atmospheric Loss (dB): %f | Rainfall Loss\
    (dB): %f | Pointing Loss (dB): %f |  Doppler (Hz): %f | \
    Link Margin (dB): %f",
    d_tracker->get_elapsed_time().ToString().c_str(), d_slant_range,
    d_elev, d_pathloss_attenuation,
    d_atmo_attenuation, d_rainfall_attenuation, d_pointing_attenuation,
    d_doppler_shift, d_link_margin_db);

  return d_total_attenuation;
}

void
leo_model_impl::estimate_link_margin()
{
  /**
   * TODO: Fix hardcoded TX power and bandwidth. Also caution because losses
   * should be negative.
   */
  d_link_margin_db = d_link_margin->calc_link_margin(
                       d_total_attenuation, get_satellite_antenna_gain(),
                       get_tracker_antenna_gain(), get_tx_power_dbm() - 30,
                       calculate_noise_floor());
}

float
leo_model_impl::calculate_noise_floor()
{

  d_noise_floor =  10 * log10(1.38e-23 * get_noise_temperature() * 1e3) +
                   get_noise_figure() + 10 * log10(get_receiver_bandwidth()) - 30.0;

  return d_noise_floor;
}

void
leo_model_impl::generate_csv_log()
{
  std::ostringstream stringStream;
  if (d_write_csv_header) {
    stringStream << "Elapsed Time (us)" << "," << "Slant Range (km)"
                 << "," << "Elevation (degrees)" << "," << "Path Loss (dB)" << ","
                 << "Atmospheric Loss (dB)" << "," << "Rainfall Loss (dB)" << ","
                 << "Pointing Loss (dB)" << "," << "Doppler Shift (Hz)" << ","
                 << "Link Margin (dB)";
    d_write_csv_header = false;
  }
  else {
    stringStream << d_tracker->get_elapsed_time().ToString().c_str()
                 << "," << d_slant_range << ","
                 << d_elev << ","
                 << d_pathloss_attenuation << "," << d_atmo_attenuation << ","
                 << d_rainfall_attenuation << "," << d_pointing_attenuation << ","
                 << d_doppler_shift << "," << d_link_margin_db;
  }
  d_csv_log = stringStream.str();
}

double
leo_model_impl::get_doppler_freq()
{
  return d_doppler_shift;
}

void
leo_model_impl::generic_work(const gr_complex *inbuffer, gr_complex *outbuffer,
                             int noutput_items, double samp_rate)
{
  const gr_complex *in = (const gr_complex *) inbuffer;
  gr_complex *out = (gr_complex *) outbuffer;

  float pl_attenuation_db;
  float total_attenuation_db;
  float tracker_antenna_gain_db;
  float satellite_antenna_gain_db;

  gr_complex attenuation_linear;

  d_elev = d_tracker->get_elevation_degrees();
  if (d_elev > 0.0) {
    d_slant_range = d_tracker->get_slant_range();
    if (d_doppler_shift_enum == DOPPLER_SHIFT) {
      d_doppler_shift = calculate_doppler_shift(
                          d_tracker->get_velocity());
      volk_32fc_s32fc_x2_rotator_32fc(outbuffer, inbuffer,
                                      (2 * M_PI * d_doppler_shift / samp_rate) / std::abs(2 * M_PI * d_doppler_shift /
                                          samp_rate),
                                      &d_phase, noutput_items);
      /* Change the pointer to simplify the rest of the logic */
      inbuffer = outbuffer;
    }
    /**
     * Get total attenuation in dB, convert it to linear and
     * multiply
     * TODO: Examine if restriction for elevation > 1 degree
     * should be set.
     */
    total_attenuation_db = calculate_total_attenuation();
    attenuation_linear = gr_complex(1.0 / std::pow(10.0f,
                                    (total_attenuation_db / 20.0f)), 0.0f);
    volk_32fc_s32fc_multiply_32fc(outbuffer, inbuffer, attenuation_linear,
                                  noutput_items);
  }
  else {
    memset(outbuffer, 0, noutput_items * sizeof(gr_complex));
    d_phase = gr_complex(1.0, 0.0);
  }
}

} /* namespace model */
} /* namespace leo */
} /* namespace gr */

