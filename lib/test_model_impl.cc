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

#include "test_model_impl.h"
#include <cstring>

namespace gr
{
  namespace leo
  {

    generic_model::generic_model_sptr
    test_model::make (tracker::tracker_sptr tracker)
    {
      return generic_model::generic_model_sptr (new test_model_impl (tracker));
    }

    test_model_impl::test_model_impl (tracker::tracker_sptr tracker) :
            generic_model ("test_model", tracker),
            d_tracker (tracker)
    {
    }

    test_model_impl::~test_model_impl ()
    {
    }

    void
    test_model_impl::generic_work (const gr_complex *inbuffer,
                                   gr_complex *outbuffer, int noutput_items)
    {
      const gr_complex *in = (const gr_complex *) inbuffer;
      gr_complex *out = (gr_complex *) outbuffer;
      d_tracker->add_elapsed_time ();
      d_tracker->get_slant_range ();

      std::cout << "Time: " << d_tracker->get_elapsed_time ()
          << "| Slant Range: " << d_tracker->get_slant_range () << " | Elevation: " << d_tracker->get_current_elevation()<< std::endl;

      memcpy (outbuffer, inbuffer, noutput_items * sizeof(gr_complex));

    }

  } /* namespace leo */
} /* namespace gr */

