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

#include "precipitation_itu_impl.h"
#include <cmath>
#include <string>
#include <leo/utils/helper.h>
#include <leo/log.h>

namespace gr
{
  namespace leo
  {
    namespace attenuation
    {

      generic_attenuation::generic_attenuation_sptr
      precipitation_itu::make (float frequency, float rainfall_rate,
                               float tracker_lontitude, float tracker_latitude,
                               float polarization,
                               precipitation_attenuation_t mode)
      {
        return generic_attenuation::generic_attenuation_sptr (
            new precipitation_itu_impl (frequency, rainfall_rate,
                                        tracker_lontitude, tracker_latitude,
                                        polarization, mode));
      }

      precipitation_itu_impl::precipitation_itu_impl (
          float frequency, float rainfall_rate, float tracker_lontitude,
          float tracker_latitude, float polarization,
          precipitation_attenuation_t mode) :
              generic_attenuation (),
              d_frequency (frequency / 1e9),
              d_rainfall_rate (rainfall_rate),
              d_tracker_lontitude (tracker_lontitude),
              d_tracker_latitude (tracker_latitude),
              d_polarization (polarization),
              d_elevation_angle (0),
              d_mode (mode),
              d_hs (1)
      {
        std::string data_path (DATA_PATH);

        d_isotherm_height = utils::parser_ITU_heatmap (
            data_path + "/ITU_RREC_P839/Lat.txt",
            data_path + "/ITU_RREC_P839/Lon.txt",
            data_path + "/ITU_RREC_P839/ITU_R-REC-P.839-4.txt",
            d_tracker_lontitude, d_tracker_latitude);
        LEO_LOG_INFO("Isotherm Height: %f", d_isotherm_height);

        if (d_mode == PRECIPITATION_ITU) {
          d_rainfall_rate = utils::parser_ITU_heatmap (
              data_path + "/ITU_RREC_P837/LAT_R001.TXT",
              data_path + "/ITU_RREC_P837/LON_R001.TXT",
              data_path + "/ITU_RREC_P837/LAT_R001.TXT", d_tracker_lontitude,
              d_tracker_latitude);
          d_polarization = 3;
          d_frequency = 1;
          std::cout << "RAINFALL ATTENUATION: " << get_attenuation (d_elevation_angle)
              << std::endl;
          exit (-1);
        }
      }

      precipitation_itu_impl::~precipitation_itu_impl ()
      {
      }

      float
      precipitation_itu_impl::get_attenuation (float elevation)
      {
        float Ls;
        float LG;
        float height_tmp;
        float LE;
        float gammar;
        float Aaverage;
        float elevation_rads = utils::degrees_to_radians(elevation);

        if ((height_tmp = d_isotherm_height - d_hs) <= 0) {
          return 0;
        }

        if (elevation < 5) {
          Ls = 2 * height_tmp
              / (std::pow (
                  (std::pow (std::sin (elevation_rads), 2)
                      + (2 * height_tmp) / EARTH_RADIUS),
                  0.5) + std::sin (elevation_rads));
        }
        else {
          Ls = height_tmp / std::cos (elevation_rads);
        }

        LG = Ls * std::cos (elevation_rads);
        gammar = get_specific_attenuation (elevation_rads);
        LE = calculate_effective_path_len (LG, d_isotherm_height, gammar,
                                           elevation_rads);
        Aaverage = gammar * LE;

        return Aaverage;
      }

      float
      precipitation_itu_impl::get_specific_attenuation (float elevation)
      {
        float gammar = 0;
        float k = 0;
        float logkh = 0;
        float logkv = 0;
        float a = 0;
        float av = 0;
        float ah = 0;
        float tilt = 45;

        for (size_t j = 0; j < d_kh.size (); j++) {
          logkh += d_kh[j][0]
              * std::exp (
                  -std::pow (
                      (std::log10 (d_frequency) - d_kh[j][1]) / d_kh[j][2], 2));
          logkv += d_kv[j][0]
              * std::exp (
                  -std::pow (
                      (std::log10 (d_frequency) - d_kv[j][1]) / d_kv[j][2], 2));
          av += d_av[j][0]
              * std::exp (
                  -std::pow (
                      (std::log10 (d_frequency) - d_av[j][1]) / d_av[j][2], 2));
          ah += d_ah[j][0]
              * std::exp (
                  -std::pow (
                      (std::log10 (d_frequency) - d_ah[j][1]) / d_ah[j][2], 2));
        }
        logkh += (d_kh[0][3] * std::log10 (d_frequency) + d_kh[0][4]);
        logkv += (d_kv[0][3] * std::log10 (d_frequency) + d_kv[0][4]);

        av += d_av[4][0]
            * std::exp (
                -std::pow ((std::log10 (d_frequency) - d_av[4][1]) / d_av[4][2],
                           2));
        av += d_av[0][3] * std::log10 (d_frequency) + d_av[0][4];

        ah += d_ah[4][0]
            * std::exp (
                -std::pow ((std::log10 (d_frequency) - d_ah[4][1]) / d_ah[4][2],
                           2));
        ah += d_ah[0][3] * std::log10 (d_frequency) + d_ah[0][4];

        switch ((size_t) d_polarization)
          {
          case VERTICAL:
            k = std::pow (10, logkv);
            a = av;
            break;
          case HORIZONTAL:
            k = std::pow (10, logkh);
            a = ah;
            break;
          case LINEAR:
          case LHCP:
          case RHCP:
            k = (std::pow (10, logkh) + std::pow (10, logkv)
                + (std::pow (10, logkh) - std::pow (10, logkv))
                    * std::pow (std::cos (elevation), 2)
                    * std::cos (2 * utils::degrees_to_radians (tilt))) / 2;
            a = (std::pow (10, logkh) * ah + std::pow (10, logkv) * av
                + (std::pow (10, logkh) * ah - std::pow (10, logkv) * av)
                    * std::pow (std::cos (elevation), 2)
                    * std::cos (2 * utils::degrees_to_radians (tilt)))
                / (2 * k);
            break;
          }

        gammar = k * std::pow (d_rainfall_rate, a);
        return gammar;
      }

      float
      precipitation_itu_impl::get_horizontal_reduction_factor (
          float LG, float specific_attenuation)
      {
        return 1
            / (1 + 0.78 * std::sqrt ((LG * specific_attenuation) / d_frequency)
                - 0.38 * (1 - std::exp (-2 * LG)));
      }

      float
      precipitation_itu_impl::calculate_effective_path_len (float LG, float hr,
                                                            float gammar,
                                                            float elevation)
      {
        float zeta;
        float hrf;
        float LR;
        float x;

        hrf = get_horizontal_reduction_factor (LG, gammar);
        zeta = std::pow (std::tan ((hr - d_hs) / (LG * hrf)), -1);

        if (utils::radians_to_degrees(zeta) > utils::radians_to_degrees(elevation)) {
          LR = LG * hrf / std::cos (elevation);
        }
        else {
          LR = (hr - d_hs) / std::sin (elevation);
        }

        if (d_tracker_latitude > 36) {
          x = utils::degrees_to_radians(36 - std::abs (d_tracker_latitude));
        }
        else {
          x = 0;
        }

        return LR
            * (1
                / (1
                    + std::sqrt (std::sin (elevation))
                        * (31 * (1 - std::exp (-elevation / (1 + x)))
                            * (std::sqrt (LR * gammar)
                                / std::pow (d_frequency, 2)) - 0.45)));
      }

    } /* namespace attenuation */
  } /* namespace leo */
} /* namespace gr */

