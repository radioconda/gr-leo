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

#ifndef INCLUDED_LEO_HELIX_ANTENNA_IMPL_H
#define INCLUDED_LEO_HELIX_ANTENNA_IMPL_H

#include "../include/leo/helix_antenna.h"
#include <vector>

namespace gr
{
  namespace leo
  {
    namespace antenna
    {

      class LEO_API helix_antenna_impl : public helix_antenna
      {

      public:
        helix_antenna_impl (uint8_t type, float frequency, int polarization,
                            size_t turns, float turn_spacing,
                            float circumference);

        ~helix_antenna_impl ();

        float
        get_gain ();

        float
        get_beamwidth ();

      private:

        size_t d_turns;
        float d_turn_spacing;
        float d_circumference;

      };
    } // namespace antenna
  } // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_YAGI_ANTENNA_IMPL_H */

