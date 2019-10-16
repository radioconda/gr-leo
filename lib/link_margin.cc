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

#include "../include/leo/link_margin.h"
#include <leo/log.h>
#include <cmath>
#include <iostream>

namespace gr {
namespace leo {

link_margin::link_margin_sptr
link_margin::make()
{
  return link_margin::link_margin_sptr(new link_margin());
}

link_margin::~link_margin()
{
}

float
link_margin::calc_link_margin(float total_loss_db,
                              float satellite_antenna_gain,
                              float tracker_antenna_gain,
                              float transmission_power_dbw,
                              float noise_floor)
{
  float signal_power_gs_input = transmission_power_dbw - total_loss_db
                                + satellite_antenna_gain + tracker_antenna_gain;

  // float gs_noise_power = BOLTZMANS_CONST + 10 * log10(GS_NOISE_TEMP)
  //                        + 10 * log10(gs_receiver_bw);
  float gs_snr = signal_power_gs_input - noise_floor;

  // TODO: Fix dynamic minimum required modulation SNR
  return gs_snr;
}
} /* namespace leo */
} /* namespace gr */

