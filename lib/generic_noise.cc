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

#include <gnuradio/io_signature.h>
#include <include/leo/generic_noise.h>

namespace gr
{
  namespace leo
  {

    generic_noise::generic_noise ()
    {
    }

    generic_noise::~generic_noise ()
    {
    }

    float
    generic_noise::measure_signal_power (const gr_complex* inbuf, size_t num)
    {
      float sum = 0;

      for (size_t i = 0; i < num; i++) {
        sum += pow (abs (inbuf[i]), 2);
      }
      return sum / num;
    }

  } /* namespace leo */
} /* namespace gr */
