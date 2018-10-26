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

#ifndef INCLUDED_LEO_ATMOSPHERE_H
#define INCLUDED_LEO_ATMOSPHERE_H

#include <leo/api.h>
#include <leo/generic_attenuation.h>

namespace gr
{
  namespace leo
  {

    /**
     * @brief Mean annual global reference atmosphere Rec. ITU-R  P.835-6
     *
     */

    class LEO_API atmosphere
    {

    public:

      atmosphere (float frequency, const atmo_gases_attenuation_t, const float surface_watervap_density,
                  const float temperature);

      ~atmosphere ();

      float
      get_attenuation ();

      void
      set_elevation_angle (float angle);

      void
      set_tracker_altitude (float altitude);

      void
      set_tracker_latitude (float latitude);

    private:
      float d_frequency;
      float d_elevation;
      float d_tracker_altitude;
      float d_tracker_latitude;

      float d_surface_watervap_density;
      float d_temperature;

      atmo_gases_attenuation_t d_atmo_gases_enum;
      generic_attenuation::generic_attenuation_sptr d_atmo_gases_attenuation;

    };

  } // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_ATMOSPHERE_H */

