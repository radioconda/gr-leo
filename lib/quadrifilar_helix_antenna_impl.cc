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

#include "quadrifilar_helix_antenna_impl.h"
#include <leo/utils/helper.h>
#include <leo/log.h>
#include <cmath>

namespace gr {
namespace leo {
namespace antenna {

generic_antenna::generic_antenna_sptr
quadrifilar_helix_antenna::make(uint8_t type, double frequency,
                                int polarization,
                                double pointing_error, double loop)
{
  return generic_antenna::generic_antenna_sptr(
           new quadrifilar_helix_antenna_impl(type, frequency, polarization,
               pointing_error, loop));
}

quadrifilar_helix_antenna_impl::quadrifilar_helix_antenna_impl(uint8_t type,
    double frequency,
    int polarization,
    double pointing_error,
    double loop) :
  generic_antenna(QUADRIFILAR_HELIX, frequency, polarization, pointing_error),
  d_loop(loop)
{
  LEO_DEBUG("QUADRIFILAR HELIX");
  LEO_DEBUG("Maximum Gain: %f", get_gain());
  LEO_DEBUG("Beamwidth: %f", get_beamwidth());
}

quadrifilar_helix_antenna_impl::~quadrifilar_helix_antenna_impl()
{
}

double
quadrifilar_helix_antenna_impl::get_gain()
{
  return 4;
}

double
quadrifilar_helix_antenna_impl::get_gain_rolloff()
{
  double error_deg = utils::radians_to_degrees(d_pointing_error);
  return -1.5 * (-4 + 10 * std::log10(1.256 * (1 + std::cos(d_pointing_error))));
}

double
quadrifilar_helix_antenna_impl::get_beamwidth()
{
  return 150;
}

} /* namespace antenna */
} /* namespace leo */
} /* namespace gr */

