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

#include "leo_model_impl.h"
#include <cstring>

namespace gr
{
  namespace leo
  {

    generic_model::generic_model_sptr
    leo_model::make (tracker::tracker_sptr tracker)
    {
      return generic_model::generic_model_sptr (new leo_model_impl (tracker));
    }

    leo_model_impl::leo_model_impl (tracker::tracker_sptr tracker) :
            generic_model ("leo_model", tracker),
            d_tracker (tracker)
    {
    }

    leo_model_impl::~leo_model_impl ()
    {
    }

    float
    leo_model_impl::calculate_free_space_path_loss (float slant_range)
    {
      float wave_length = LIGHT_SPEED
          / d_tracker->get_satellite_info ()->get_freq_uplink ();

      return 22.0 + 20 * std::log10 ((slant_range * 1e3) / wave_length);
    }

    void
    leo_model_impl::generic_work (const gr_complex *inbuffer,
                                  gr_complex *outbuffer, int noutput_items)
    {
      const gr_complex *in = (const gr_complex *) inbuffer;
      gr_complex *out = (gr_complex *) outbuffer;

      d_tracker->add_elapsed_time ();
      double slant_range = d_tracker->get_slant_range ();
      float PL = calculate_free_space_path_loss (slant_range);

      if (slant_range) {
        memcpy (outbuffer, inbuffer, noutput_items * sizeof(gr_complex));
      }
      else {
        memset (outbuffer, 0, noutput_items * sizeof(gr_complex));
      }

      std::cout << "Time: " << d_tracker->get_elapsed_time ()
          << " | Slant Range: " << slant_range << " | Path Loss (dB): " << PL
          << std::endl;

    }

  } /* namespace leo */
} /* namespace gr */

