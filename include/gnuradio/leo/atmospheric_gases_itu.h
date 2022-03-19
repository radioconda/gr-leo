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

#ifndef INCLUDED_LEO_ATMOSPHERIC_GASES_ITU_H
#define INCLUDED_LEO_ATMOSPHERIC_GASES_ITU_H

#include <gnuradio/leo/api.h>
#include <gnuradio/leo/generic_attenuation.h>

namespace gr {
namespace leo {
namespace attenuation {
/*!
 * \brief This class represents the attenuation induced by
 * atmospheric gases along the slant path between the ground station and the
 * orbiting satellite.
 *
 * \ingroup attenuation
 *
 * \details The implementation follows the method described in the
 * Annex 1 of the ITU P.676 recommendation, that provides an estimate of gaseous
 * attenuation computed by a summation of individual absorption lines. The method is
 * valid for the frequency range 1-1000 GHz.
 *
 * A reference standard atmosphere as described in ITU P.835-6 is used in order
 * to calculate the pressure, temperature and water-vapour pressure along the
 * atmospheric path.
 *
 * Also ITU P.435 is used to extract the atmospheric radio refractive index using
 * the reference standard atmosphere.
 */
class LEO_API atmospheric_gases_itu : virtual public generic_attenuation {

public:

  /*!
   * \brief Return a shared_ptr to a gr::leo::generic_attenuation
   *
   * \param surface_watervap_density Water vapour density in g/m3
   *
   * \return a boost::shared_ptr<generic_attenuation> pointer
   */
  static generic_attenuation::generic_attenuation_sptr
  make(double surface_watervap_density);

};
} // namespace attenuation
} // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_ATMOSPHERIC_GASES_ITU_H */

