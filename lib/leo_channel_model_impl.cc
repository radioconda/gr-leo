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
#include <iostream>

namespace gr
{
  namespace leo
  {

    leo_channel_model::sptr
    leo_channel_model::make (const float sample_rate,
                             const float time_resolution,
                             const std::string& tle_title,
                             const std::string& tle_1, const std::string& tle_2,
                             const float gs_lat, const float gs_lon,
                             const float gs_alt, const std::string& obs_start,
                             const std::string& obs_end)
    {
      return gnuradio::get_initial_sptr (
          new leo_channel_model_impl (sample_rate, time_resolution, tle_title,
                                      tle_1, tle_2, gs_lat, gs_lon, gs_alt,
                                      obs_start, obs_end));
    }

    /*
     * The private constructor
     */
    leo_channel_model_impl::leo_channel_model_impl (
        const float sample_rate, const float time_resolution_us,
        const std::string& tle_title, const std::string& tle_1,
        const std::string& tle_2, const float gs_lat, const float gs_lon,
        const float gs_alt, const std::string& obs_start,
        const std::string& obs_end) :
            gr::sync_block ("leo_channel_model",
                            gr::io_signature::make (1, 1, sizeof(gr_complex)),
                            gr::io_signature::make (1, 1, sizeof(gr_complex))),
            d_sample_rate (sample_rate),
            d_time_resolution_us (time_resolution_us),
            d_time_resolution_samples ((d_sample_rate * d_time_resolution_us) / 1e6),
            d_tracker (
                sat_tracker (tle_title, tle_1, tle_2, gs_lat, gs_lon, gs_alt,
                             obs_start, obs_end))
    {
      set_output_multiple((d_sample_rate * d_time_resolution_us)/1e6);

      std::cout << "Time resolution (us) " << d_time_resolution_us << std::endl;
      std::cout << "Time resolution (samples) " << d_time_resolution_samples << std::endl;

    }

    /*
     * Our virtual destructor.
     */
    leo_channel_model_impl::~leo_channel_model_impl ()
    {
    }

    int
    leo_channel_model_impl::work (int noutput_items,
                                  gr_vector_const_void_star &input_items,
                                  gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];


      memcpy (out, in, noutput_items * sizeof(gr_complex));
      for (size_t t=0; t<noutput_items/d_time_resolution_samples; t++) {
        d_tracker.add_elapsed_time(d_time_resolution_samples);
        d_tracker.get_slant_range();
//        std::cout << "Time: " << d_tracker.get_elapsed_time() << "| Slant Range: " << d_tracker.get_slant_range() << std::endl;
      }
      return noutput_items;
    }

  } /* namespace leo */
} /* namespace gr */

