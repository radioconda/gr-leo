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

#ifndef INCLUDED_LEO_GENERIC_ANTENNA_H
#define INCLUDED_LEO_GENERIC_ANTENNA_H

#include <leo/api.h>
#include <string>
#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>

namespace gr {
namespace leo {

/*!
 * \brief Parent class for antenna objects.
 * \ingroup antenna
 * \details
 *
 * Parent of an antenna class that will simulate different types
 * of antennas.
 */
class LEO_API generic_antenna {

public:
  static int base_unique_id;

  /*!
   * The enumeration that defines the type of the antenna
   */
  enum antenna_t {
    YAGI,
    HELIX,
    PARABOLIC_REFLECTOR,
    CANTED_TURNSTYLE,
    CUSTOM,
    MONOPOLE,
    DIPOLE,
    QUADRIFILAR_HELIX
  };

  uint8_t d_type;

  double d_frequency;
  double d_pointing_error;

  int d_polarization;
  int my_id;

  int
  unique_id();

  /*!
   * \brief Get the frequency of the antenna.
   * \return the frequency in Hz.
   */
  double
  get_frequency();

  /*!
   * \brief Set the pointing error of the antenna.
   * \param error the pointing error in degrees.
   */
  void
  set_pointing_error(double error);

  /*!
   * \brief Get the pointing error of the antenna.
   * \return the pointing error in degrees.
   */
  double
  get_pointing_error();

  /*!
   * \brief Get the polarization of the antenna.
   * \return the gr::leo::generic_antenna::Polarization enum.
   */
  int
  get_polarization();

  /*!
   * \brief Get the wavelength of the antenna.
   * \return the wavelength in meters.
   */
  double
  get_wavelength();

  /*!
   * \brief Get the gain of the antenna. This pure virtual
   * function MUST be implemented by every derived class.
   * \return the gain in dBiC.
   */
  virtual double
  get_gain() = 0;

  /*!
   * \brief Get the beamwidth of the antenna. This pure virtual
   * function MUST be implemented by every derived class.
   * \return the beamwidth in degrees.
   */
  virtual double
  get_beamwidth() = 0;

  /*!
   * \brief Get the the gain roll-off of the antenna.
   * \return the gain roll-off in dB.
   */
  virtual double
  get_gain_rolloff() = 0;

  typedef boost::shared_ptr<generic_antenna> generic_antenna_sptr;

  virtual
  ~generic_antenna();

  /*!
   * \brief The constructor of generic_antenna class
   *
   * \param type The enumeration that defines the type of the antenna
   * \param frequency The frequency of the antenna in Hz
   * \param polarization The enumeration that defines the antenna
   * polarization
   *
   * \return a boost::shared_ptr to the constructed tracker object.
   */
  generic_antenna(uint8_t type, double frequency, int polarization,
                  double pointing_error);

  generic_antenna(void) {};
};
} // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_GENERIC_ANTENNA_H */

