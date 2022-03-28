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

#ifndef INCLUDED_LEO_LINK_MARGIN_H
#define INCLUDED_LEO_LINK_MARGIN_H

#include <gnuradio/leo/api.h>
#include <memory>

namespace gr {
namespace leo {

class LEO_API link_margin {

public:

  ~link_margin();

  using link_margin_sptr = std::shared_ptr<link_margin>;

  static link_margin::link_margin_sptr
  make();

  double
  calc_link_margin(double total_loss_db, double satellite_antenna_gain,
                   double tracker_antenna_gain,
                   double transmission_power_dbw, double noise_floor);

};
} // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_LINK_MARGIN_H */

