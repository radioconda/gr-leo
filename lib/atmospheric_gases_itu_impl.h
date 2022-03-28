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

#ifndef INCLUDED_LEO_ATMOSPHERIC_GASES_ITU_IMPL_H
#define INCLUDED_LEO_ATMOSPHERIC_GASES_ITU_IMPL_H

#include "../include/gnuradio/leo/atmospheric_gases_itu.h"
#include <vector>

namespace gr {
namespace leo {
namespace attenuation {

class LEO_API atmospheric_gases_itu_impl : public atmospheric_gases_itu {

public:
  atmospheric_gases_itu_impl(double surface_watervap_density);

  ~atmospheric_gases_itu_impl();

  typedef enum atmo_element {
    OXYGEN = 1, WATER_VAPOUR = 2
  } atmo_element_t;

  double
  get_attenuation();

private:

  double d_temperature;
  double d_oxygen_pressure;
  double d_water_pressure;
  double d_surface_watervap_density;

  /*!
   * Spectroscopic data for oxygen attenuation
   * Rec. ITU-R P.676-11
   */
  std::vector<std::vector<double>> d_table1 {
    { 50.474214, 0.975, 9.651, 6.69, 0, 2.566, 6.85 },
    { 50.987745, 2.529, 8.653, 7.17, 0, 2.246, 6.8 },
    { 51.50336, 6.193, 7.709, 7.64, 0, 1.947, 6.729 },
    { 52.021429, 14.32, 6.819, 8.11, 0, 1.667, 6.64 },
    { 52.542418, 31.24, 5.983, 8.58, 0, 1.388, 6.526 },
    { 53.066934, 64.29, 5.201, 9.06, 0, 1.349, 6.206 },
    { 53.595775, 124.6, 4.474, 9.55, 0, 2.227, 5.085 },
    { 54.130025, 227.3, 3.8, 9.96, 0, 3.17, 3.75 },
    { 54.67118, 389.7, 3.182, 10.37, 0, 3.558, 2.654 },
    { 55.221384, 627.1, 2.618, 10.89, 0, 2.56, 2.952 },
    { 55.783815, 945.3, 2.109, 11.34, 0, -1.172, 6.135 },
    { 56.264774, 543.4, 0.014, 17.03, 0, 3.525, -0.978 },
    { 56.363399, 1331.8, 1.654, 11.89, 0, -2.378, 6.547 },
    { 56.968211, 1746.6, 1.255, 12.23, 0, -3.545, 6.451 },
    { 57.612486, 2120.1, 0.91, 12.62, 0, -5.416, 6.056 },
    { 58.323877, 2363.7, 0.621, 12.95, 0, -1.932, 0.436 },
    { 58.446588, 1442.1, 0.083, 14.91, 0, 6.768, -1.273 },
    { 59.164204, 2379.9, 0.387, 13.53, 0, -6.561, 2.309 },
    { 59.590983, 2090.7, 0.207, 14.08, 0, 6.957, -0.776 },
    { 60.306056, 2103.4, 0.207, 14.15, 0, -6.395, 0.699 },
    { 60.434778, 2438, 0.386, 13.39, 0, 6.342, -2.825 },
    { 61.150562, 2479.5, 0.621, 12.92, 0, 1.014, -0.584 },
    { 61.800158, 2275.9, 0.91, 12.63, 0, 5.014, -6.619 },
    { 62.41122, 1915.4, 1.255, 12.17, 0, 3.029, -6.759 },
    { 62.486253, 1503, 0.083, 15.13, 0, -4.499, 0.844 },
    { 62.997984, 1490.2, 1.654, 11.74, 0, 1.856, -6.675 },
    { 63.568526, 1078, 2.108, 11.34, 0, 0.658, -6.139 },
    { 64.127775, 728.7, 2.617, 10.88, 0, -3.036, -2.895 },
    { 64.67891, 461.3, 3.181, 10.38, 0, -3.968, -2.590 },
    { 65.224078, 274, 3.8, 9.96, 0, -3.528, -3.680 },
    { 65.764779, 153, 4.473, 9.55, 0, -2.548, -5.002 },
    { 66.302096, 80.4, 5.2, 9.06, 0, -1.660, -6.091 },
    { 66.836834, 39.8, 5.982, 8.58, 0, -1.680, -6.393 },
    { 67.369601, 18.56, 6.818, 8.11, 0, -1.956, -6.475 },
    { 67.900868, 8.172, 7.708, 7.64, 0, -2.216, -6.545 },
    { 68.431006, 3.397, 8.652, 7.17, 0, -2.492, -6.600 },
    { 68.960312, 1.334, 9.65, 6.69, 0, -2.773, -6.650 },
    { 118.750334, 940.3, 0.01, 16.64, 0, -0.439, 0.079 },
    { 368.498246, 67.4, 0.048, 16.4, 0, 0, 0 },
    { 424.76302, 637.7, 0.044, 16.4, 0, 0, 0 },
    { 487.249273, 237.4, 0.049, 16, 0, 0, 0 },
    { 715.392902, 98.1, 0.145, 16, 0, 0, 0 },
    { 773.83949, 572.3, 0.141, 16.2, 0, 0, 0 },
    { 834.145546, 183.1, 0.145, 14.7, 0, 0, 0 } };

  /*!
   * Spectroscopic data for water-vapour attenuation
   * Rec. ITU-R P.676-11
   */
  std::vector<std::vector<double>> d_table2 {
    { 22.23508, 0.1079, 2.144, 26.38, 0.76, 5.087, 1 },
    { 67.80396, 0.0011, 8.732, 28.58, 0.69, 4.93, 0.82 },
    { 119.99594, 0.0007, 8.353, 29.48, 0.7, 4.78, 0.79 },
    { 183.310087, 2.273, 0.668, 29.06, 0.77, 5.022, 0.85 },
    { 321.22563, 0.047, 6.179, 24.04, 0.67, 4.398, 0.54 },
    { 325.152888, 1.514, 1.541, 28.23, 0.64, 4.893, 0.74 },
    { 336.227764, 0.001, 9.825, 26.93, 0.69, 4.74, 0.61 },
    { 380.197353, 11.67, 1.048, 28.11, 0.54, 5.063, 0.89 },
    { 390.134508, 0.0045, 7.347, 21.52, 0.63, 4.81, 0.55 },
    { 437.346667, 0.0632, 5.048, 18.45, 0.6, 4.23, 0.48 },
    { 439.150807, 0.9098, 3.595, 20.07, 0.63, 4.483, 0.52 },
    { 443.018343, 0.192, 5.048, 15.55, 0.6, 5.083, 0.5 },
    { 448.001085, 10.41, 1.405, 25.64, 0.66, 5.028, 0.67 },
    { 470.888999, 0.3254, 3.597, 21.34, 0.66, 4.506, 0.65 },
    { 474.689092, 1.26, 2.379, 23.2, 0.65, 4.804, 0.64 },
    { 488.490108, 0.2529, 2.852, 25.86, 0.69, 5.201, 0.72 },
    { 503.568532, 0.0372, 6.731, 16.12, 0.61, 3.98, 0.43 },
    { 504.482692, 0.0124, 6.731, 16.12, 0.61, 4.01, 0.45 },
    { 547.67644, 0.9785, 0.158, 26, 0.7, 4.5, 1 },
    { 552.02096, 0.184, 0.158, 26, 0.7, 4.5, 1 },
    { 556.935985, 497, 0.159, 30.86, 0.69, 4.552, 1 },
    { 620.700807, 5.015, 2.391, 24.38, 0.71, 4.856, 0.68 },
    { 645.766085, 0.0067, 8.633, 18, 0.6, 4, 0.5 },
    { 658.00528, 0.2732, 7.816, 32.1, 0.69, 4.14, 1 },
    { 752.033113, 243.4, 0.396, 30.86, 0.68, 4.352, 0.84 },
    { 841.051732, 0.0134, 8.177, 15.9, 0.33, 5.76, 0.45 },
    { 859.965698, 0.1325, 8.055, 30.6, 0.68, 4.09, 0.84 },
    { 899.303175, 0.0547, 7.914, 29.85, 0.68, 4.53, 0.9 },
    { 902.611085, 0.0386, 8.429, 28.65, 0.7, 5.1, 0.95 },
    { 906.205957, 0.1836, 5.11, 24.08, 0.7, 4.7, 0.53 },
    { 916.171582, 8.4, 1.441, 26.73, 0.7, 5.15, 0.78 },
    { 923.112692, 0.0079, 10.293, 29, 0.7, 5, 0.8 },
    { 970.315022, 9.009, 1.919, 25.5, 0.64, 4.94, 0.67 },
    { 987.926764, 134.6, 0.257, 29.85, 0.68, 4.55, 0.9 } };

  /*!
   * \brief Get the temperature at a specific altitude in the atmosphere
   * \return The temperature in Kelvin
   */
  double
  get_temperature(double alt);

  /*!
   * \brief Get the dry air pressure at a specific altitude in the atmosphere
   * \return The pressure in hPa
   */
  double
  get_pressure(double alt);

  /*!
   * \brief Get the water-vapour pressure at a specific altitude in the atmosphere
   * \return The pressure in hPa
   */
  double
  get_water_vapour_pressure(double alt);

  double
  geometric_to_geopotential(double alt);

  double
  geopotential_to_geometric(double alt);

  double
  S(size_t index, atmo_element_t element);

  double
  F(size_t index, atmo_element_t element);

  double
  ND();

  double
  N(atmo_element_t element);

  double
  gamma();

  double
  nh(double temperature, double oxygen_pressure,
     double watevapour_pressure);

  double
  a(double an, double rn, double delta);

  double
  alpha(size_t n, double rn, double delta, double prev_alpha);

  double
  beta(size_t n, double rn, double delta, double prev_alpha);

};
} // namespace attenuation
} // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_ATMOSPHERIC_GASES_ITU_IMPL_H */

