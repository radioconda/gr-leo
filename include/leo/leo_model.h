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

#ifndef INCLUDED_LEO_LEO_MODEL_H
#define INCLUDED_LEO_LEO_MODEL_H

#include <leo/api.h>
#include <leo/generic_model.h>

namespace gr {
namespace leo {
namespace model {

/*!
 * \brief Low Earth orbit (LEO) channel model.
 * \ingroup model
 * \details
 * It accepts a complex input signal and appropriately
 * applies free-space path-loss attenuation, Doppler frequency shift
 * and atmospheric/ionosperic attenation.
 *
 */
class LEO_API leo_model : virtual public generic_model {

public:
  static generic_model::generic_model_sptr
  make(tracker::tracker_sptr tracker, const uint8_t mode,
       const uint8_t fspl_attenuation_enum,
       const uint8_t pointing_attenuation_enum,
       const uint8_t doppler_shift_enum,
       const uint8_t atmo_gases_attenuation,
       const uint8_t precipitation_attenuation,
       const float surface_watervap_density = 7.5,
       const float temperature = 0, const float rainfall_rate = 25);

  leo_model()
  {
  }
  ;

};

} //namespace
} // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_LEO_MODEL_H */

