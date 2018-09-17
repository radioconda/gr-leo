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

#ifndef INCLUDED_LEO_LEO_CHANNEL_MODEL_IMPL_H
#define INCLUDED_LEO_LEO_CHANNEL_MODEL_IMPL_H

#include <leo/leo_channel_model.h>
#include <leo/sat_tracker.h>

namespace gr
{
  namespace leo
  {

    class leo_channel_model_impl : public leo_channel_model
    {
    private:
      const float d_sample_rate;
      const float d_time_resolution_us;

      size_t d_time_resolution_samples;

      sat_tracker d_tracker;

    public:
      leo_channel_model_impl (const float sample_rate,
                              const float time_resolution,
                              const std::string& tle_title,
                              const std::string& tle_1,
                              const std::string& tle_2, const float gs_lat,
                              const float gs_lon, const float gs_alt,
                              const std::string& obs_start,
                              const std::string& obs_end);
      ~leo_channel_model_impl ();

      // Where all the action really happens
      int
      work (int noutput_items, gr_vector_const_void_star &input_items,
            gr_vector_void_star &output_items);
    };

  } // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_LEO_CHANNEL_MODEL_IMPL_H */

