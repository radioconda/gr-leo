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

#include "custom_antenna_impl.h"
#include <leo/log.h>
#include <cmath>

namespace gr
{
  namespace leo
  {
    namespace antenna
    {

      generic_antenna::generic_antenna_sptr
      custom_antenna::make (uint8_t type, float frequency, int polarization,
                            float pointing_error, float gain, float beamwidth, float rolloff_gain)
      {
        return generic_antenna::generic_antenna_sptr (
            new custom_antenna_impl (type, frequency, polarization,
                                     pointing_error, gain, beamwidth, rolloff_gain));
      }

      custom_antenna_impl::custom_antenna_impl (uint8_t type, float frequency,
                                                int polarization,
                                                float pointing_error,
                                                float gain, float beamwidth, float rolloff_gain) :
              generic_antenna (CUSTOM, frequency, polarization, pointing_error),
              d_gain (gain),
              d_beamwidth (beamwidth),
              d_rolloff_gain (rolloff_gain)
      {
        LEO_DEBUG("CUSTOM");
        LEO_DEBUG("Maximum Gain: %f", get_gain ());
        LEO_DEBUG("Beamwidth: %f", get_beamwidth ());
      }

      custom_antenna_impl::~custom_antenna_impl ()
      {
      }

      float
      custom_antenna_impl::get_gain ()
      {
        return d_gain;
      }

      float
      custom_antenna_impl::get_gain_rolloff ()
      {
        return d_rolloff_gain;
      }

      float
      custom_antenna_impl::get_beamwidth ()
      {
        return d_beamwidth;
      }

    } /* namespace antenna */
  } /* namespace leo */
} /* namespace gr */

