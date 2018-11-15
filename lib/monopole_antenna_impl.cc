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

#include "monopole_antenna_impl.h"
#include <leo/log.h>
#include <leo/utils/helper.h>
#include <cmath>
#include <limits>

namespace gr
{
  namespace leo
  {
    namespace antenna
    {

      generic_antenna::generic_antenna_sptr
      monopole_antenna::make (uint8_t type, float frequency, int polarization,
                              float pointing_error)
      {
        return generic_antenna::generic_antenna_sptr (
            new monopole_antenna_impl (type, frequency, polarization,
                                       pointing_error));
      }

      monopole_antenna_impl::monopole_antenna_impl (uint8_t type,
                                                    float frequency,
                                                    int polarization,
                                                    float pointing_error) :
              generic_antenna (MONOPOLE, frequency, polarization, pointing_error)
      {
        LEO_DEBUG("MONOPOLE");
        LEO_DEBUG("Maximum Gain: %f", get_gain ());
        LEO_DEBUG("Beamwidth: %f", get_beamwidth ());
      }

      monopole_antenna_impl::~monopole_antenna_impl ()
      {
      }

      float
      monopole_antenna_impl::get_gain ()
      {
        return 2.15;
      }

      float
      monopole_antenna_impl::get_gain_rolloff ()
      {
        float error_deg = utils::radians_to_degrees (d_pointing_error);
        if (error_deg < 100) {
          if (!error_deg) {
            return 162.1;
          }
          return -10 * std::log10 (std::cos (utils::degrees_to_radians(90 - error_deg)));
        }
        else {
          LEO_WARN("No signal. Monopole antenna's pointing error > 100");
          return std::numeric_limits<double>::infinity();
        }
      }

      float
      monopole_antenna_impl::get_beamwidth ()
      {
        return 156.2;
      }

    } /* namespace antenna */
  } /* namespace leo */
} /* namespace gr */

