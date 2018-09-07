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
#include "leo_channel_model_impl.h"
#include <sgp4/CoordTopocentric.h>
#include <sgp4/CoordGeodetic.h>
#include <sgp4/Observer.h>
#include <sgp4/SGP4.h>
#include <iostream>

namespace gr {
  namespace leo {

    leo_channel_model::sptr
    leo_channel_model::make()
    {
      return gnuradio::get_initial_sptr
        (new leo_channel_model_impl());
    }

    /*
     * The private constructor
     */
    leo_channel_model_impl::leo_channel_model_impl()
      : gr::sync_block("leo_channel_model",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex)))
    {
      Observer obs(51.507406923983446, -0.12773752212524414, 0.05);
          Tle tle = Tle("UK-DMC 2                ",
              "1 35683U 09041C   12289.23158813  .00000484  00000-0  89219-4 0  5863",
              "2 35683  98.0221 185.3682 0001499 100.5295 259.6088 14.69819587172294");
          SGP4 sgp4(tle);

      std::cout << tle << std::endl;
    }

    /*
     * Our virtual destructor.
     */
    leo_channel_model_impl::~leo_channel_model_impl()
    {
    }

    int
    leo_channel_model_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];

      memcpy(out, in, noutput_items*sizeof(gr_complex));

      return noutput_items;
    }

  } /* namespace leo */
} /* namespace gr */

