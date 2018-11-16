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

#include "free_space_path_loss_impl.h"
#include <cmath>
#include <leo/log.h>

namespace gr
{
  namespace leo
  {
    namespace attenuation
    {

      generic_attenuation::generic_attenuation_sptr
      free_space_path_loss::make (float rx_antenna_gain, float tx_antenna_gain)
      {
        return generic_attenuation::generic_attenuation_sptr (
            new free_space_path_loss_impl (rx_antenna_gain, tx_antenna_gain));
      }

      free_space_path_loss_impl::free_space_path_loss_impl (float rx_antenna_gain, float tx_antenna_gain) :
          d_rx_antenna_gain (rx_antenna_gain),
          d_tx_antenna_gain (tx_antenna_gain),
              generic_attenuation ()
      {
      }

      free_space_path_loss_impl::~free_space_path_loss_impl ()
      {
      }

      float
      free_space_path_loss_impl::get_attenuation ()
      {
        float attenuation = 0;
        float path_loss = 0;

        path_loss = 92.45 + 20 * std::log10 (slant_range * frequency);
        attenuation = path_loss - (d_rx_antenna_gain + d_tx_antenna_gain);

        return attenuation;
      }

    } /* namespace attenuation */
  } /* namespace leo */
} /* namespace gr */

