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

#ifndef INCLUDED_LEO_YAGI_ANTENNA_H
#define INCLUDED_LEO_YAGI_ANTENNA_H

#include <leo/api.h>
#include <leo/generic_antenna.h>
#include <string>

namespace gr
{
  namespace leo
  {
    namespace antenna
    {
      /*!
       * \brief Class that represents a Yagi antenna.
       *
       * \details
       *
       * The yagi_antenna class extends the generic_antenna class
       * to simulate the behavior of a yagi antenna.
       */
      class LEO_API yagi_antenna : virtual public generic_antenna
      {

      public:

        /*!
         * \param type The enumeration that defines the type of the antenna
         * \param frequency The frequency of the antenna in Hz
         * \param polarization The enumeration that defines the antenna
         * polarization
         * \param boom_length The length of the antenna boom in meters
         *
         * \return a boost::shared_ptr to the constructed tracker object.
         */
        static generic_antenna::generic_antenna_sptr
        make (uint8_t type, float frequency, int polarization,
              float boom_length);

      };
    } // namespace antenna
  } // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_YAGI_ANTENNA_H */

