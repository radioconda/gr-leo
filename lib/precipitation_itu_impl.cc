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
#include <filesystem>
#include <string>
#include <gnuradio/constants.h>
#include <gnuradio/leo/utils/helper.h>
#include <gnuradio/leo/log.h>

namespace gr {
namespace leo {
namespace attenuation {

generic_attenuation::generic_attenuation_sptr
precipitation_itu::make(double rainfall_rate, double tracker_lontitude,
                        double tracker_latitude, double tracker_altitude,
                        impairment_enum_t mode)
{
  return generic_attenuation::generic_attenuation_sptr(
           new precipitation_itu_impl(rainfall_rate, tracker_lontitude,
                                      tracker_latitude, tracker_altitude,
                                      mode));
}

precipitation_itu_impl::precipitation_itu_impl(
  double rainfall_rate, double tracker_lontitude, double tracker_latitude,
  double tracker_altitude, impairment_enum_t mode) :
  generic_attenuation(),
  d_rainfall_rate(rainfall_rate),
  d_tracker_lontitude(tracker_lontitude),
  d_tracker_latitude(tracker_latitude),
  d_tracker_altitude(tracker_altitude),
  d_mode(mode),
  d_hs(tracker_altitude)
{

  /**
   * TODO: Extract info about Height above sea-level d_h ITU data
   */
  std::filesystem::path gr_prefix = gr::prefix();
  std::filesystem::path data_path = (gr_prefix / GR_LEO_REL_DATA_PATH).lexically_normal();

  d_isotherm_height = utils::parser_ITU_heatmap(
                        (data_path / "ITU_RREC_P839" / "Lat.txt").string(),
                        (data_path / "ITU_RREC_P839" / "Lon.txt").string(),
                        (data_path / "ITU_RREC_P839" / "ITU_R-REC-P.839-4.txt").string(),
                        d_tracker_lontitude, d_tracker_latitude);

  /**
   * TODO: Parse ITU data P.1511 to extract height above sea level
   */


  if (d_mode == PRECIPITATION_ITU) {
    d_rainfall_rate = utils::parser_ITU_heatmap(
                        (data_path / "ITU_RREC_P837" / "LAT_R001.TXT").string(),
                        (data_path / "ITU_RREC_P837" / "LON_R001.TXT").string(),
                        (data_path / "ITU_RREC_P837" / "LAT_R001.TXT").string(), d_tracker_lontitude,
                        d_tracker_latitude);
  }
}

precipitation_itu_impl::~precipitation_itu_impl()
{
}

double
precipitation_itu_impl::get_attenuation()
{
  double Ls;
  double LG;
  double height_tmp;
  double LE;
  double gammar;
  double Aaverage;

  if ((height_tmp = d_isotherm_height - d_hs) <= 0) {
    return 0;
  }

  if (utils::radians_to_degrees(elevation_angle) < 5) {
    Ls = 2 * height_tmp
         / (std::pow(
              (std::pow(std::sin(elevation_angle), 2)
               + (2 * height_tmp) / EARTH_RADIUS),
              0.5) + std::sin(elevation_angle));
  }
  else {
    Ls = height_tmp / std::cos(elevation_angle);
  }

  LG = Ls * std::cos(elevation_angle);
  gammar = get_specific_attenuation();
  LE = calculate_effective_path_len(LG, d_isotherm_height, gammar);
  Aaverage = gammar * LE;

  return Aaverage;
}

double
precipitation_itu_impl::get_specific_attenuation()
{
  double gammar = 0;
  double k = 0;
  double logkh = 0;
  double logkv = 0;
  double a = 0;
  double av = 0;
  double ah = 0;
  /**
   * TODO: Move tilt in generic_attenuation class and
   * remove constant value
   */
  double tilt = 45;

  for (size_t j = 0; j < d_kh.size(); j++) {
    logkh += d_kh[j][0]
             * std::exp(
               -std::pow((std::log10(frequency) - d_kh[j][1]) / d_kh[j][2],
                         2));
    logkv += d_kv[j][0]
             * std::exp(
               -std::pow((std::log10(frequency) - d_kv[j][1]) / d_kv[j][2],
                         2));
    av += d_av[j][0]
          * std::exp(
            -std::pow((std::log10(frequency) - d_av[j][1]) / d_av[j][2],
                      2));
    ah += d_ah[j][0]
          * std::exp(
            -std::pow((std::log10(frequency) - d_ah[j][1]) / d_ah[j][2],
                      2));
  }
  logkh += (d_kh[0][3] * std::log10(frequency) + d_kh[0][4]);
  logkv += (d_kv[0][3] * std::log10(frequency) + d_kv[0][4]);

  av += d_av[4][0]
        * std::exp(
          -std::pow((std::log10(frequency) - d_av[4][1]) / d_av[4][2],
                    2));
  av += d_av[0][3] * std::log10(frequency) + d_av[0][4];

  ah += d_ah[4][0]
        * std::exp(
          -std::pow((std::log10(frequency) - d_ah[4][1]) / d_ah[4][2],
                    2));
  ah += d_ah[0][3] * std::log10(frequency) + d_ah[0][4];

  switch (polarization) {
  case LINEAR_VERTICAL:
    k = std::pow(10, logkv);
    a = av;
    break;
  case LINEAR_HORIZONTAL:
    k = std::pow(10, logkh);
    a = ah;
    break;
  case LHCP:
  case RHCP:
    k = (std::pow(10, logkh) + std::pow(10, logkv)
         + (std::pow(10, logkh) - std::pow(10, logkv))
         * std::pow(std::cos(elevation_angle), 2)
         * std::cos(2 * utils::degrees_to_radians(tilt))) / 2;
    a = (std::pow(10, logkh) * ah + std::pow(10, logkv) * av
         + (std::pow(10, logkh) * ah - std::pow(10, logkv) * av)
         * std::pow(std::cos(elevation_angle), 2)
         * std::cos(2 * utils::degrees_to_radians(tilt)))
        / (2 * k);
    break;
  default:
    throw std::runtime_error("Invalid antenna polarization!");
  }

  gammar = k * std::pow(d_rainfall_rate, a);
  return gammar;
}

double
precipitation_itu_impl::get_horizontal_reduction_factor(
  double LG, double specific_attenuation)
{
  return 1
         / (1 + 0.78 * std::sqrt((LG * specific_attenuation) / frequency)
            - 0.38 * (1 - std::exp(-2 * LG)));
}

double
precipitation_itu_impl::calculate_effective_path_len(double LG, double hr,
    double gammar)
{
  double zeta;
  double hrf;
  double LR;
  double x;

  hrf = get_horizontal_reduction_factor(LG, gammar);
  zeta = std::pow(std::tan((hr - d_hs) / (LG * hrf)), -1);

  if (utils::radians_to_degrees(zeta)
      > utils::radians_to_degrees(elevation_angle)) {
    LR = LG * hrf / std::cos(elevation_angle);
  }
  else {
    LR = (hr - d_hs) / std::sin(elevation_angle);
  }

  if (d_tracker_latitude > 36) {
    x = utils::degrees_to_radians(36 - std::abs(d_tracker_latitude));
  }
  else {
    x = 0;
  }

  return LR
         * (1
            / (1
               + std::sqrt(std::sin(elevation_angle))
               * (31 * (1 - std::exp(-elevation_angle / (1 + x)))
                  * (std::sqrt(LR * gammar) / std::pow(frequency, 2))
                  - 0.45)));
}

} /* namespace attenuation */
} /* namespace leo */
} /* namespace gr */

