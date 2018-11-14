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

#include "parabolic_reflector_antenna_impl.h"
#include <leo/utils/helper.h>
#include <leo/log.h>
#include <cmath>

namespace gr
{
  namespace leo
  {
    namespace antenna
    {

      generic_antenna::generic_antenna_sptr
      parabolic_reflector_antenna::make (uint8_t type, float frequency,
                                         int polarization, float pointing_error, float diameter,
                                         float aperture_efficiency)
      {
        return generic_antenna::generic_antenna_sptr (
            new parabolic_reflector_antenna_impl (type, frequency, polarization, pointing_error,
                                                  diameter,
                                                  aperture_efficiency));
      }

      parabolic_reflector_antenna_impl::parabolic_reflector_antenna_impl (
          uint8_t type, float frequency, int polarization, float pointing_error, float diameter,
          float aperture_efficiency) :
              generic_antenna (PARABOLIC_REFLECTOR, frequency, polarization, pointing_error),
              d_diameter (diameter),
              d_aperture_efficiency (aperture_efficiency)

      {
        LEO_DEBUG("Parabolic Reflector");
        LEO_DEBUG("Maximum Gain: %f", get_gain ());
        LEO_DEBUG("Beamwidth: %f", get_beamwidth ());
      }

      parabolic_reflector_antenna_impl::~parabolic_reflector_antenna_impl ()
      {
      }

      float
      parabolic_reflector_antenna_impl::get_gain ()
      {
        return 20.4 + 20 * std::log10 (d_diameter)
            + 20 * std::log10 (d_frequency / 1e6 / 1000)
            + 10 * std::log10 (d_aperture_efficiency / 100);
      }


      float
      parabolic_reflector_antenna_impl::get_gain_rolloff ()
      {
        float error_deg = utils::radians_to_degrees (d_pointing_error);
        float tmp = 2*(error_deg*(79.76/get_beamwidth()));
        return -10 * std::log10 (3282.1 * (std::pow(std::sin (tmp),2)/std::pow(tmp,2)));
      }

      float
      parabolic_reflector_antenna_impl::get_beamwidth ()
      {
        return 21 / (d_diameter * (d_frequency / 1e6 / 1000));
      }

    } /* namespace antenna */
  } /* namespace leo */
} /* namespace gr */

