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
#include "channel_model_impl.h"
#include <iostream>

namespace gr
{
  namespace leo
  {

    channel_model::sptr
    channel_model::make (const float sample_rate,
                         generic_model::generic_model_sptr model,
                         tracker::tracker_sptr tracker,
                         const uint8_t mode)
    {
      return gnuradio::get_initial_sptr (
          new channel_model_impl (sample_rate, model, tracker, mode));
    }

    /*
     * The private constructor
     */
    channel_model_impl::channel_model_impl (
        const float sample_rate, generic_model::generic_model_sptr model,
        tracker::tracker_sptr tracker, const uint8_t mode) :
            gr::sync_block ("channel_model",
                            gr::io_signature::make (1, 1, sizeof(gr_complex)),
                            gr::io_signature::make (1, 1, sizeof(gr_complex))),
            d_sample_rate (sample_rate),
            d_time_resolution_us (
                tracker->get_time_resolution_us ()),
            d_time_resolution_samples (
                (d_sample_rate * d_time_resolution_us) / 1e6),
            d_model (model),
            d_tracker (tracker),
            d_mode (mode)
    {
      set_output_multiple (d_time_resolution_samples);
      d_model->set_mode (mode);
      d_model->set_tracker(tracker);
    }

    /*
     * Our virtual destructor.
     */
    channel_model_impl::~channel_model_impl ()
    {
    }

    int
    channel_model_impl::work (int noutput_items,
                              gr_vector_const_void_star &input_items,
                              gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];

      for (size_t t = 0; t < noutput_items / d_time_resolution_samples; t++) {
        if (d_tracker->is_observation_over ()) {
          return WORK_DONE;
        }
        d_model->generic_work (&in[d_time_resolution_samples * t],
                               &out[d_time_resolution_samples * t],
                               d_time_resolution_samples);
      }

      return noutput_items;
    }

  } /* namespace leo */
} /* namespace gr */

