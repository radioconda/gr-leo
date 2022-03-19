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

#ifndef INCLUDED_LEO_QUADRIFILAR_HELIX_ANTENNA_IMPL_H
#define INCLUDED_LEO_QUADRIFILAR_HELIX_ANTENNA_IMPL_H

#include "../include/gnuradio/leo/quadrifilar_helix_antenna.h"
#include <vector>

namespace gr {
namespace leo {
namespace antenna {
/*!
 * \brief Class that represents a Quadrifilar Helix antenna.
 * \ingroup antenna
 * \details
 *
 * The helix_antenna class extends the generic_antenna class
 * to simulate the behavior of a quadrifilar helix antenna.
 */
class LEO_API quadrifilar_helix_antenna_impl : public
  quadrifilar_helix_antenna {

public:
  /*!
   * \brief The constructor of quadrifilar_helix_antenna class
   *
   * \param type The enumeration that defines the type of the antenna
   * \param frequency The frequency of the antenna in Hz
   * \param polarization The enumeration that defines the antenna
   * polarization
   * \param pointing_error The pointing error of the antenna in degrees.
   * \param loop The loop of the quadrifilar helix antenna
   */
  quadrifilar_helix_antenna_impl(uint8_t type, double frequency, int polarization,
                                 double pointing_error, double loop);

  ~quadrifilar_helix_antenna_impl();

  /*!
   * \brief Get the gain of the quadrifilar helix antenna. This is the implementation
   * of the parent's pure virtual function for the quadrifilar helix antenna.
   * \return the gain in dBiC.
   */
  double
  get_gain();

  /*!
   * \brief Get the the gain roll-off of the antenna.
   * \return the gain roll-off in dB.
   */
  double
  get_gain_rolloff();

  /*!
   * \brief Get the beamwidth of the quadrifilar helix antenna. This is the implementation
   * of the parent's pure virtual function for the quadrifilar helix antenna.
   * \return the beamwidth.
   */
  double
  get_beamwidth();

private:

  double d_loop;

};
} // namespace antenna
} // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_QUADRIFILAR_HELIX_ANTENNA_IMPL_H */

