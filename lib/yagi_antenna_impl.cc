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

#include "yagi_antenna_impl.h"
#include <leo/utils/helper.h>
#include <leo/log.h>
#include <cmath>
#include <algorithm>

namespace gr
{
  namespace leo
  {
    namespace antenna
    {

      generic_antenna::generic_antenna_sptr
      yagi_antenna::make (uint8_t type, float frequency, int polarization,
                          float pointing_error, float boom_length)
      {
        return generic_antenna::generic_antenna_sptr (
            new yagi_antenna_impl (type, frequency, polarization,
                                   pointing_error, boom_length));
      }

      yagi_antenna_impl::yagi_antenna_impl (uint8_t type, float frequency,
                                            int polarization,
                                            float pointing_error,
                                            float boom_length) :
              generic_antenna (YAGI, frequency, polarization, pointing_error),
              d_boom_length (boom_length)
      {
        d_optimum_elements = find_optimum_elements ();
        LEO_DEBUG("Yagi");
        LEO_DEBUG("Maximum Gain: %f", get_gain ());
        LEO_DEBUG("Beamwidth: %f", get_beamwidth ());
      }

      yagi_antenna_impl::~yagi_antenna_impl ()
      {
      }

      float
      yagi_antenna_impl::get_gain ()
      {
        for (size_t i = 0; i < d_yagi_performance.size (); i++) {
          if (std::get<0> (d_yagi_performance[i]) > d_boom_length) {
            return std::get<2> (d_yagi_performance[i - 1]);
          }
        }
        throw std::runtime_error ("Invalid Yagi boom length");
      }

      float
      yagi_antenna_impl::get_gain_rolloff (float pointing_error) {
        return 2*utils::radians_to_degrees(pointing_error)*get_beamwidth();
      }

      float
      yagi_antenna_impl::get_beamwidth ()
      {
        return sqrt (40000 / std::pow (10, get_gain () / 10));
      }

      float
      yagi_antenna_impl::find_optimum_elements ()
      {
        for (size_t i = 0; i < d_yagi_performance.size (); i++) {
          if (std::get<0> (d_yagi_performance[i]) > d_boom_length) {
            return std::get<1> (d_yagi_performance[i - 1]);
          }
        }
        throw std::runtime_error ("Invalid Yagi boom length");
      }

    } /* namespace antenna */
  } /* namespace leo */
} /* namespace gr */

