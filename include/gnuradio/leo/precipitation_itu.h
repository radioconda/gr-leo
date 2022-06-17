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

#ifndef INCLUDED_LEO_PRECIPITATION_ITU_H
#define INCLUDED_LEO_PRECIPITATION_ITU_H

#include <gnuradio/leo/api.h>
#include <gnuradio/leo/generic_attenuation.h>
#include <gnuradio/leo/leo_types.h>

namespace gr {
namespace leo {
namespace attenuation {
/*!
 * \brief Precipitation loss following the ITU P.618 recommendation
 */
class LEO_API precipitation_itu : virtual public generic_attenuation {

public:

  static generic_attenuation::generic_attenuation_sptr
  make(double rainfall_rate, double tracker_lontitude,
       double tracker_latitude, double tracker_altitude,
       impairment_enum_t mode);

};
} // namespace attenuation
} // namespace leo
} // namespace gr

#endif /* INCLUDED_LEOPRECIPITATION_ITU_H */

