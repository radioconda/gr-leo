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

#ifndef INCLUDED_LEO_GENERIC_NOISE_H
#define INCLUDED_LEO_GENERIC_NOISE_H

#include <leo/api.h>

namespace gr
{
  namespace leo
  {

    class LEO_API generic_noise
    {

    public:

      typedef boost::shared_ptr<generic_noise> generic_noise_sptr;

      generic_noise ();

      virtual
      ~generic_noise ();

      virtual void
      add_noise (gr_complex* outbuf, const gr_complex* inbuf, size_t num,
                 float snr) = 0;

      float
      measure_signal_power (const gr_complex* inbuf, size_t num);

    };

  } // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_GENERIC_NOISE_H */

