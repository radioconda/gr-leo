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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "monopole_antenna_impl.h"
#include <leo/log.h>
#include <cmath>

namespace gr
{
  namespace leo
  {
    namespace antenna
    {

      generic_antenna::generic_antenna_sptr
      monopole_antenna::make (uint8_t type, float frequency, int polarization)
      {
        return generic_antenna::generic_antenna_sptr (
            new monopole_antenna_impl (type, frequency, polarization));
      }

      monopole_antenna_impl::monopole_antenna_impl (uint8_t type, float frequency,
                                              int polarization) :
              generic_antenna (HELIX, frequency, polarization)
      {
        LEO_DEBUG("MONOPOLE");
        LEO_DEBUG("Maximum Gain: %f", get_gain());
        LEO_DEBUG("Beamwidth: %f", get_beamwidth());
      }

      monopole_antenna_impl::~monopole_antenna_impl ()
      {
      }

      float
      monopole_antenna_impl::get_gain ()
      {
        return 2.15;
      }

      float
      monopole_antenna_impl::get_beamwidth ()
      {
        return 156.2;
      }

    } /* namespace antenna */
  } /* namespace leo */
} /* namespace gr */

