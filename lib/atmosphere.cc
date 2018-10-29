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
#include <leo/atmospheric_gases_regression.h>
#include <leo/precipitation_itu.h>
#include <leo/atmosphere.h>
#include <leo/log.h>

namespace gr
{
  namespace leo
  {

    /**
     * TODO: Pass tracker as argument to avoid initialization issues
     */
    atmosphere::atmosphere (float frequency,
                            const atmo_gases_attenuation_t atmo_gases,
                            const float surface_watervap_density,
                            const float temperature) :
            d_frequency (frequency / 1e9),
            d_elevation (0),
            d_tracker_altitude(0),
            d_atmo_gases_enum (atmo_gases),
            d_surface_watervap_density (surface_watervap_density),
            d_temperature (temperature),
            d_atmo_gases_attenuation(NULL)
    {
      switch (d_atmo_gases_enum)
        {
        case ATMO_GASES_ITU:
          d_atmo_gases_attenuation = attenuation::atmospheric_gases_itu::make (
              d_frequency, d_surface_watervap_density);
          break;
        case ATMO_GASES_REGRESSION:
          d_atmo_gases_attenuation = attenuation::atmospheric_gases_regression::make (
                        d_frequency, d_surface_watervap_density, d_temperature);
          break;
        case NONE:
          break;
        default:
          throw std::runtime_error ("Invalid atmospheric gases attenuation!");
        }

      d_precipitation_attenuation = attenuation::precipitation_itu::make(d_frequency, 8.5, d_tracker_altitude, d_tracker_latitude);
    }

    atmosphere::~atmosphere ()
    {
    }

    void
    atmosphere::set_elevation_angle (float angle)
    {
      d_elevation = angle;
    }

    void
    atmosphere::set_tracker_altitude (float altitude)
    {
      d_tracker_altitude = altitude;
    }

    void
    atmosphere::set_tracker_latitude (float latitude)
    {
      d_tracker_latitude = latitude;
    }


    float
    atmosphere::get_attenuation ()
    {
      float total_atmo_attenuation = 0;
      if (d_atmo_gases_attenuation != NULL) {
        total_atmo_attenuation = d_atmo_gases_attenuation->get_attenuation (
            d_elevation);
      }
      return total_atmo_attenuation;
    }

  } /* namespace leo */
} /* namespace gr */

