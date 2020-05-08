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

#ifndef INCLUDED_LEO_GENERIC_ATTENUATION_H
#define INCLUDED_LEO_GENERIC_ATTENUATION_H

#include <leo/api.h>
#include <string>
#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>

namespace gr {
namespace leo {

/*!
 * \brief Parent class for attenuation objects.
 *
 * \details This is an abstract class that must be derived by
 * other classes in order to simulate a specific type of attenuation.
 * Holds information, in the form of static variables, about the operating frequency,
 * the elevation angle, the slant range and the polarization of the tracker
 * at a specific time instance.
 *
 * Each derived class must implement the pure virtual function get_attenuation
 * according to the attenuation it describes, using the static variables of the
 * parent class.
 *
 */
class LEO_API generic_attenuation {

public:

  /*!
   * \brief Get the estimated attenuation. This pure virtual
   * function MUST be implemented by every derived class.
   * \return the attenuation in dB.
   */
  virtual double
  get_attenuation() = 0;

  /*!
   * \brief Set frequency static variable
   * \param freq The frequency in Hz
   */
  static void
  set_frequency(double freq);

  /*!
   * \brief Set slant range static variable
   * \param range The range in km
   */
  static void
  set_slant_range(double range);

  /*!
   * \brief Set polarization static variable
   * \param polar The polarization enumeration
   */
  static void
  set_polarization(uint8_t polar);

  /*!
   * \brief Set elevation angle static variable
   * \param elev_angle The elevation angle in radians
   */
  static void
  set_elevation_angle(double elev_angle);

  typedef boost::shared_ptr<generic_attenuation> generic_attenuation_sptr;

  static generic_attenuation::generic_attenuation_sptr
  make();

  generic_attenuation();

  virtual
  ~generic_attenuation();

protected:
  static double frequency;
  static double elevation_angle;
  static double slant_range;
  static uint8_t polarization;
};

} // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_GENERIC_ATTENUATION_H */

