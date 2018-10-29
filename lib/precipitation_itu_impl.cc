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

#include "precipitation_itu_impl.h"
#include <cmath>
#include <string>
#include <leo/utils/helper.h>
#include <leo/log.h>

namespace gr
{
  namespace leo
  {
    namespace attenuation
    {

      generic_attenuation::generic_attenuation_sptr
      precipitation_itu::make (float frequency, float rainfall_rate,
                             float tracker_altitude, float tracker_latitude)
      {
        return generic_attenuation::generic_attenuation_sptr (
            new precipitation_itu_impl (frequency, rainfall_rate,
                                      tracker_altitude, tracker_latitude));
      }

      precipitation_itu_impl::precipitation_itu_impl (float frequency,
                                                  float rainfall_rate,
                                                  float tracker_altitude,
                                                  float tracker_latitude) :
              generic_attenuation (),
              d_frequency (frequency),
              d_rainfall_rate (rainfall_rate),
              d_tracker_altitude (tracker_altitude),
              d_tracker_latitude (tracker_latitude),
              d_elevation_angle (0)
      {
        std::string data_path (DATA_PATH);
        float isotherm_height;
        isotherm_height = utils::parser_ITU_heatmap (data_path + "/Lat.txt",
                                   data_path + "/Lon.txt",
                                   data_path + "/ITU_R-REC-P.839-4.txt",
                                   2,
                                   86);
      }

      precipitation_itu_impl::~precipitation_itu_impl ()
      {
      }

      float
      precipitation_itu_impl::get_attenuation (float elevation)
      {
        float attenuation;

        return attenuation;
      }

    } /* namespace attenuation */
  } /* namespace leo */
} /* namespace gr */

