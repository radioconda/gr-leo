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

#ifndef INCLUDED_LEO_CHANNEL_MODEL_H
#define INCLUDED_LEO_CHANNEL_MODEL_H

#include <leo/api.h>
#include <leo/generic_model.h>
#include <gnuradio/sync_block.h>
#include <string>

namespace gr {
namespace leo {

/*!
 * \brief General channel model block that takes in a model
 * variable object (derived from gr::leo::general_model) for use
 * in a flowgraph.
 *
 * \details
 * This block uses a model variable object (derived from
 * gr::leo::generic_model) to simulate different space channels in a
 * flowgraph. The model variable takes the incoming signal and
 * applies the appropriate signal effects and attenuation according
 * to the described channel.
 */
class LEO_API channel_model : virtual public gr::sync_block {
public:
  typedef boost::shared_ptr<channel_model> sptr;
  /*!
   * \brief Return a shared_ptr to a new instance of leo::channel_model.
   *
   * \param sample_rate The sampling rate of the block
   * \param model An LEO_API model object (See gr::leo::generic_model)
   */
  static sptr
  make(const float sample_rate, generic_model::generic_model_sptr model,
       const uint8_t noise_type, float snr = 0, float imp = 1);

};

} // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_CHANNEL_MODEL_H */

