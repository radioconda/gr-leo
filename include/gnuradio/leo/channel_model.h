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

#include <gnuradio/leo/api.h>
#include <gnuradio/leo/generic_model.h>
#include <gnuradio/leo/leo_types.h>
#include <gnuradio/sync_block.h>
#include <memory>
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

  using sptr = std::shared_ptr<channel_model>;

  /*!
   * \brief Return a shared_ptr to a new instance of leo::channel_model.
   *
   * \param sample_rate The sampling rate of the block
   * \param model An LEO_API model object (See gr::leo::generic_model)
   */
  static sptr
  make(const double sample_rate, generic_model::generic_model_sptr model,
       const noise_t noise_type, const bool store_csv, const char *filename);

};

} // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_CHANNEL_MODEL_H */

