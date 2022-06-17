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

#ifndef INCLUDED_LEO_HELIX_ANTENNA_H
#define INCLUDED_LEO_HELIX_ANTENNA_H

#include <gnuradio/leo/api.h>
#include <gnuradio/leo/generic_antenna.h>
#include <gnuradio/leo/leo_types.h>
#include <string>

namespace gr {
namespace leo {
namespace antenna {
/*!
 * \brief Class that represents a helix antenna.
 * \details
 *
 * The helix_antenna class extends the generic_antenna class
 * to simulate the behavior of a helix antenna.
 */
class LEO_API helix_antenna : virtual public generic_antenna {

public:

  /*!
   * \param type The enumeration that defines the type of the antenna
   * \param frequency The frequency of the antenna in Hz
   * \param polarization The enumeration that defines the antenna
   * polarization
   * \param pointing_error The pointing error of the antenna in degrees.
   * \param turns The number of turns
   * \param turn_spacing The turn spacing
   * \param circumference The circumference
   *
   * \return a boost::shared_ptr to the constructed tracker object.
   */
  static generic_antenna::generic_antenna_sptr
  make(antenna_t type, double frequency, polarization_t polarization,
       double pointing_error, size_t turns, double turn_spacing,
       double circumference);

  helix_antenna() {};

};
} // namespace antenna
} // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_HELIX_ANTENNA_H */

