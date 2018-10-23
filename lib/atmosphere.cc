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

#include <gnuradio/io_signature.h>
#include <leo/atmospheric_gases_itu.h>
#include <leo/atmosphere.h>
#include <leo/log.h>

namespace gr
{
  namespace leo
  {

    /**
     *
     */
    atmosphere::atmosphere (float frequency,
                            const atmo_gases_attenuation_t atmo_gases) :
            d_frequency (frequency / 1e9),
            d_elevation (0),
            d_atmo_gases_enum (atmo_gases)
    {
      switch (d_atmo_gases_enum)
        {
        case ATMO_GASES_ITU:
          d_atmo_gases_attenuation = attenuation::atmospheric_gases_itu::make (
              d_frequency);
          break;
        case NONE:
          break;
        default:
          throw std::runtime_error ("Invalid atmospheric gases attenuation!");
        }
    }

    atmosphere::~atmosphere ()
    {
    }

    void
    atmosphere::set_elevation_angle (float angle)
    {
      d_elevation = angle;
    }

    float
    atmosphere::get_attenuation ()
    {
      float total_atmo_attenuation;
      if (d_atmo_gases_attenuation != NULL) {
        total_atmo_attenuation = d_atmo_gases_attenuation->get_attenuation (
            d_elevation);
      }
      return total_atmo_attenuation;
    }

  } /* namespace leo */
} /* namespace gr */

