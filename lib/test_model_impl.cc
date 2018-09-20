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

namespace gr {
  namespace leo {

      generic_model::generic_model_sptr
      test_model::make(tracker::tracker_sptr tracker)
      {
        return generic_model::generic_model_sptr
          (new test_model_impl(tracker));
      }

      test_model_impl::test_model_impl(tracker::tracker_sptr tracker)
        : generic_model("test_model")
      {
      }

      test_model_impl::~test_model_impl()
      {
      }

      void
      test_model_impl::generic_work(void *inbuffer, void *outbuffer)
      {
        const gr_complex *in = (const gr_complex *) inbuffer;
        gr_complex *out = (gr_complex *) outbuffer;

      }

  } /* namespace leo */
} /* namespace gr */


