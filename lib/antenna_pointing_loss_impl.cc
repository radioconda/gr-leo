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

#include "antenna_pointing_loss_impl.h"
#include <leo/log.h>

namespace gr {
namespace leo {
namespace attenuation {

generic_attenuation::generic_attenuation_sptr
antenna_pointing_loss::make(generic_antenna::generic_antenna_sptr
                            tracker_antenna,
                            generic_antenna::generic_antenna_sptr satellite_antenna)
{
  return generic_attenuation::generic_attenuation_sptr(
           new antenna_pointing_loss_impl(tracker_antenna, satellite_antenna));
}

antenna_pointing_loss_impl::antenna_pointing_loss_impl(
  generic_antenna::generic_antenna_sptr tracker_antenna,
  generic_antenna::generic_antenna_sptr satellite_antenna) :
  d_tracker_antenna(tracker_antenna),
  d_satellite_antenna(satellite_antenna),
  generic_attenuation()
{
}

antenna_pointing_loss_impl::~antenna_pointing_loss_impl()
{
}

float
antenna_pointing_loss_impl::get_attenuation()
{
  float attenuation = 0;
//        attenuation += d_tracker_antenna->get_gain_rolloff();
  attenuation += d_satellite_antenna->get_gain_rolloff();
  return attenuation;
}

} /* namespace attenuation */
} /* namespace leo */
} /* namespace gr */

