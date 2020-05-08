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

#ifndef INCLUDED_LEO_ATMOSPHERIC_GASES_REGRESSION_H
#define INCLUDED_LEO_ATMOSPHERIC_GASES_REGRESSION_H

#include <leo/api.h>
#include <leo/generic_attenuation.h>
#include <string>

namespace gr {
namespace leo {
namespace attenuation {
/*!
 * \brief Atmospheric gas following the method described in
 * Radiowave Propagation in Satellite Communications,
 * Louis J. Ippolito Jr, 1986. The method is
 * valid for the frequency range 1-350 GHz.
 *
 * \ingroup attenuation
 */
class LEO_API atmospheric_gases_regression : virtual public
  generic_attenuation {

public:
  /*!
   * \brief Return a shared_ptr to a gr::leo::generic_attenuation
   *
   * \param watervap Water vapour density in g/m3
   * \param temperature Surface temperature in Celsius
   *
   * \return a boost::shared_ptr<generic_attenuation> pointer
   */
  static generic_attenuation::generic_attenuation_sptr
  make(double watervap, double temperature);

};
} // namespace attenuation
} // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_ATMOSPHERIC_GASES_REGRESSION_H */

