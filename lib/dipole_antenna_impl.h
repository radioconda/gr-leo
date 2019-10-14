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

#ifndef INCLUDED_LEO_DIPOLE_ANTENNA_IMPL_H
#define INCLUDED_LEO_DIPOLE_ANTENNA_IMPL_H

#include "../include/leo/dipole_antenna.h"
#include <vector>

namespace gr {
namespace leo {
namespace antenna {
/*!
 * \brief Class that represents a dipole antenna.
 * \ingroup antenna
 * \details
 *
 * The dipole_antenna class extends the generic_antenna class
 * to simulate the behavior of a dipole antenna.
 */
class LEO_API dipole_antenna_impl : public dipole_antenna {

public:
  /*!
   * \brief The constructor of dipole_antenna class
   *
   * \param type The enumeration that defines the type of the antenna
   * \param frequency The frequency of the antenna in Hz
   * \param polarization The enumeration that defines the antenna
   * polarization
   * \param pointing_error The pointing error of the antenna in degrees.
   */
  dipole_antenna_impl(uint8_t type, float frequency, int polarization,
                      float pointing_error);

  ~dipole_antenna_impl();

  /*!
   * \brief Get the gain of the dipole antenna. This is the implementation
   * of the parent's pure virtual function for the helix antenna.
   * \return the gain in dBiC.
   */
  float
  get_gain();

  /*!
   * \brief Get the the gain roll-off of the antenna.
   * \return the gain roll-off in dB.
   */
  float
  get_gain_rolloff();

  /*!
   * \brief Get the beamwidth of the dipole antenna. This is the implementation
   * of the parent's pure virtual function for the dipole antenna.
   * \return the beamwidth.
   */
  float
  get_beamwidth();

};
} // namespace antenna
} // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_DIPOLE_ANTENNA_IMPL_H */

