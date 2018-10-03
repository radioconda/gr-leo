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

namespace gr
{
  namespace leo
  {

    /*!
     * \brief Parent class for LEO_API antenna objects.
     *
     * \details
     *
     * Parent of a antenna variable class for LEO_API that will fit
     * into the gr::leo::antenna block to handle antenna simulation.
     *
     * We create objects from LEO_API-derived classes to go into the
     * actual GNU Radio antenna block. Each object contains its own
     * state and so there should be a one-to-one mapping of an LEO_API
     * object and a GR antenna.
     *
     * This is a pure virtual class and must be derived from by a
     * child class.
     */
    class LEO_API generic_antenna
    {

    public:
      static int base_unique_id;

      enum Antennas {Yagi, Helix, Custom};

      uint8_t d_type;

      float d_frequency;

      int d_polarization;
      int my_id;

      int
      unique_id ();

      std::string
      alias ()
      {
        return (boost::format ("%s%d") % d_type % unique_id ()).str ();
      }

      float
      get_frequency ();

      int
      get_polarization ();

      float
      get_wavelength ();

      virtual float
      get_gain () = 0;

      virtual float
      get_beamwidth () = 0;

      typedef boost::shared_ptr<generic_antenna> generic_antenna_sptr;

      static generic_antenna::generic_antenna_sptr
      make (uint8_t type, float frequency, int polarization);

      generic_antenna (void)
      {
      }
      ;

      virtual
      ~generic_antenna ();

      generic_antenna (uint8_t type, float frequency, int polarization);

    };
  } // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_GENERIC_ANTENNA_H */

