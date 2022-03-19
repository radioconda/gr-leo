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

#include "helix_antenna_impl.h"
#include <gnuradio/leo/utils/helper.h>
#include <gnuradio/leo/log.h>
#include <cmath>

namespace gr {
namespace leo {
namespace antenna {

generic_antenna::generic_antenna_sptr
helix_antenna::make(uint8_t type, double frequency, int polarization,
                    double pointing_error, size_t turns,
                    double turn_spacing, double circumference)
{
  return generic_antenna::generic_antenna_sptr(
           new helix_antenna_impl(type, frequency, polarization,
                                  pointing_error, turns, turn_spacing,
                                  circumference));
}

helix_antenna_impl::helix_antenna_impl(uint8_t type, double frequency,
                                       int polarization,
                                       double pointing_error,
                                       size_t turns, double turn_spacing,
                                       double circumference) :
  generic_antenna(HELIX, frequency, polarization, pointing_error),
  d_turns(turns),
  d_turn_spacing(turn_spacing),
  d_circumference(circumference)
{
  LEO_DEBUG("HELIX");
  LEO_DEBUG("Maximum Gain: %f", get_gain());
  LEO_DEBUG("Beamwidth: %f", get_beamwidth());
}

helix_antenna_impl::~helix_antenna_impl()
{
}

double
helix_antenna_impl::get_gain()
{
  return 10
         * std::log10(
           15 * std::pow(d_circumference, 2) * d_turns * d_turn_spacing);
}

double
helix_antenna_impl::get_gain_rolloff()
{
  double error_deg = utils::radians_to_degrees(d_pointing_error);
  double tmp = 2 * error_deg * (79.76 / get_beamwidth());
  if (error_deg > 0) {
    return -10
           * std::log10(
             3282.81
             * std::pow(std::sin(utils::degrees_to_radians(tmp)), 2)
             / std::pow(tmp, 2));
  }
  else {
    return 0;
  }
}

double
helix_antenna_impl::get_beamwidth()
{
  return 115 / (d_circumference * std::sqrt(d_turns * d_turn_spacing));
}

} /* namespace antenna */
} /* namespace leo */
} /* namespace gr */

