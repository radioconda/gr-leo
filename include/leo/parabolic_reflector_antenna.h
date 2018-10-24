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

#ifndef INCLUDED_LEO_PARABOLIC_REFLECTOR_ANTENNA_H
#define INCLUDED_LEO_PARABOLIC_REFLECTOR_ANTENNA_H

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
       * \brief Parabolic antenna
       */
      class LEO_API parabolic_reflector_antenna : virtual public generic_antenna
      {

      public:

        static generic_antenna::generic_antenna_sptr
        make (uint8_t type, float frequency, int polarization, float diameter, float aperture_efficiency);

      };
    } // namespace antenna
  } // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_YAGI_ANTENNA_H */

