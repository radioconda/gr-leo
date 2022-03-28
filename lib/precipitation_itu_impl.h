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

#ifndef INCLUDED_LEO_PRECIPITATION_ITU_IMPL_H
#define INCLUDED_LEO_PRECIPITATION_ITU_IMPL_H

#include <vector>
#include "../include/gnuradio/leo/precipitation_itu.h"

namespace gr {
namespace leo {
namespace attenuation {

class LEO_API precipitation_itu_impl : public precipitation_itu {

public:
  precipitation_itu_impl(double rainfall_rate, double tracker_lontitude,
                         double tracker_latitude, double tracker_altitude,
                         impairment_enum_t mode);

  ~precipitation_itu_impl();

  double
  get_attenuation();

private:

  double d_rainfall_rate;
  double d_tracker_lontitude;
  double d_tracker_latitude;
  double d_tracker_altitude;
  double d_hs;
  double d_isotherm_height;
  impairment_enum_t d_mode;

  /**
   * Coefficient kH
   * Rec. ITU-R P.838-3
   */
  static const std::vector<std::vector<double>> d_kh;

  /**
   * Coefficient aH
   * Rec. ITU-R P.838-3
   */
  static const std::vector<std::vector<double>> d_ah;

  /**
   * Coefficient kV
   * Rec. ITU-R P.838-3
   */
  static const std::vector<std::vector<double>> d_kv;

  /**
   * Coefficient aV
   * Rec. ITU-R P.838-3
   */
  static const std::vector<std::vector<double>> d_av;

  double
  get_zero_degree_isotherm_height(double lat, double lon);

  double
  get_specific_attenuation();

  double
  get_horizontal_reduction_factor(double LG, double specific_attenuation);

  double
  calculate_effective_path_len(double LG, double hr, double gammar);

};

const std::vector<std::vector<double>> precipitation_itu_impl::d_kh({
  { -5.33980, -0.10008, 1.13098, -0.18961, 0.71147 },
  { -0.35351, 1.269708, 0.45400, -0.18961, 0.71147 },
  { -0.23789, 0.86036, 0.15354, -0.18961, 0.71147 },
  { -0.94158, 0.64552, 0.16817, -0.18961, 0.71147 } });

const std::vector<std::vector<double>> precipitation_itu_impl::d_ah({
  { -0.14318, 1.82442, -0.55187, 0.67849, -1.95537 },
  { 0.29591, 0.77564, 0.19822, 0.67849, -1.95537 },
  { 0.32177, 0.63773, 0.13164, 0.67849, -1.95537 },
  { -5.37610, -0.96230, 1.47828, 0.67849, -1.95537 },
  { 16.1721, -3.29980, 3.43990, 0.67849, -1.95537 } });

const std::vector<std::vector<double>> precipitation_itu_impl::d_kv({
  { -3.80595, 0.56934, 0.81061, -0.16398, 0.63297 },
  { -3.44965, -0.22911, 0.51059, -0.16398, 0.63297 },
  { -0.39902, 0.73042, 0.11899, -0.16398, 0.63297 },
  { 0.50167, 1.07319, 0.27195, -0.16398, 0.63297 } });

const std::vector<std::vector<double>> precipitation_itu_impl::d_av({
  { -0.07771, 2.33840, -0.76284, -0.053739, 0.83433 },
  { 0.56727, 0.95545, 0.54039, -0.053739, 0.83433 },
  { -0.20238, 1.14520, 0.26809, -0.053739, 0.83433 },
  { -48.2991, 0.791669, 0.116226, -0.053739, 0.83433 },
  { 48.5833, 0.791459, 0.116479, -0.053739, 0.83433 } });

} // namespace attenuation
} // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_PRECIPITATION_ITU_IMPL_H */

