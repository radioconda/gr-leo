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

#ifndef INCLUDED_LEO_PARABOLIC_REFLECTOR_ANTENNA_IMPL_H
#define INCLUDED_LEO_PARABOLIC_REFLECTOR_ANTENNA_IMPL_H

#include "../include/gnuradio/leo/parabolic_reflector_antenna.h"
#include <vector>

namespace gr {
namespace leo {
namespace antenna {

/*!
 * \brief Class that represents a parabolic reflector antenna.
 * \ingroup antenna
 * \details
 *
 * The parabolic_reflector_antenna class extends the generic_antenna class
 * to simulate the behavior of a parabolic reflector antenna.
 */
class LEO_API parabolic_reflector_antenna_impl : public
  parabolic_reflector_antenna {

  /*!
   * \brief The constructor of parabolic_reflector_antenna class
   *
   * \param type The enumeration that defines the type of the antenna
   * \param frequency The frequency of the antenna in Hz
   * \param polarization The enumeration that defines the antenna
   * polarization
   * \param pointing_error The pointing error of the antenna in degrees.
   * \param diameter The diameter of the antenna in meters.
   * \param aperture_efficiency The aperture_efficiency efficiency.
   *
   */
public:
  parabolic_reflector_antenna_impl(uint8_t type, double frequency,
                                   int polarization, double pointing_error, double diameter,
                                   double aperture_efficiency);

  ~parabolic_reflector_antenna_impl();

  /*!
   * \brief Get the gain of the parabolic reflector antenna. This is the implementation
   * of the parent's pure virtual function for the parabolic reflector antenna.
   * \return the gain in dBiC.
   */
  double
  get_gain();

  /*!
   * \brief Get the beamwidth of the parabolic reflector antenna. This is the implementation
   * of the parent's pure virtual function for the parabolic reflector antenna.
   * \return the beamwidth
   */
  double
  get_beamwidth();

  /*!
   * \brief Get the the gain roll-off of the antenna.
   * \return the gain roll-off in dB.
   */
  double
  get_gain_rolloff();

private:

  double d_diameter;
  double d_aperture_efficiency;

};
} // namespace antenna
} // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_PARABOLIC_REFLECTOR_ANTENNA_IMPL_H */

