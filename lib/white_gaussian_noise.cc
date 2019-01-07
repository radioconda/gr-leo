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
#include <include/leo/white_gaussian_noise.h>

namespace gr
{
  namespace leo
  {
    namespace noise
    {

      generic_noise::generic_noise_sptr
      white_gaussian_noise::make ()
      {
        return generic_noise::generic_noise_sptr (
            new white_gaussian_noise ());
      }

      white_gaussian_noise::white_gaussian_noise () :
              generic_noise ()
      {
      }

      white_gaussian_noise::~white_gaussian_noise ()
      {
      }

      void
      white_gaussian_noise::add_noise (gr_complex* outbuf, const gr_complex* inbuf,
                                       size_t num, float snr, float imp)
      {
        gr_complex ns;
        float snr_linear;
        float measured;

        measured = measure_signal_power (inbuf, num);

        snr_linear = 1000 * pow (10, snr / 10) ;
        
        for (size_t i = 0; i < num; i++) {
          ns = gr_complex(sqrt ((imp*snr_linear) / 2))
              * gr_complex (d_rng.gasdev (), d_rng.gasdev ());
          outbuf[i] = inbuf[i] + ns;
        }
        
      }
    } // namespace noise
  } /* namespace leo */
} /* namespace gr */
