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

namespace gr {
  namespace leo {

    class leo_channel_model_impl : public leo_channel_model
    {
     private:
      // Nothing to declare in this block.

     public:
      leo_channel_model_impl();
      ~leo_channel_model_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_LEO_CHANNEL_MODEL_IMPL_H */

