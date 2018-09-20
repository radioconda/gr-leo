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

#ifndef INCLUDED_LEO_TRACKER_H
#define INCLUDED_LEO_TRACKER_H

#include <leo/api.h>
#include <leo/satellite.h>
#include <libsgp4/CoordTopocentric.h>
#include <libsgp4/CoordGeodetic.h>
#include <libsgp4/Observer.h>
#include <libsgp4/SGP4.h>
#include <iostream>
#include <vector>
#include <string>
#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>

namespace gr
{
  namespace leo
  {

//    typedef struct
//    {
//      DateTime aos;
//      DateTime los;
//      double max_elevation;
//    } pass_details_t;

    /*!
     * \brief <+description+>
     *
     */
    class LEO_API tracker
    {

    public:
      static int base_unique_id;

      int my_id;

      int
      unique_id ();

    public:
      typedef boost::shared_ptr<tracker> tracker_sptr;

      static tracker_sptr
      make (satellite::satellite_sptr satellite_info, const float gs_lat, const float gs_lon,
            const float gs_alt, const std::string& obs_start,
            const std::string& obs_end, const std::string& name);

      tracker (satellite::satellite_sptr satellite_info, const float gs_lat, const float gs_lon,
               const float gs_alt, const std::string& obs_start,
               const std::string& obs_end, const std::string& name);

      ~tracker ();

      double
      get_slant_range ();

      void
      add_elapsed_time (size_t microseconds);

      DateTime
      get_elapsed_time ();

      DateTime
      parse_ISO_8601_UTC (const std::string& datetime);

    private:

      Observer d_observer;

      Tle d_tle;
      SGP4 d_sgp4;

      DateTime d_obs_start;
      DateTime d_obs_end;
      DateTime d_obs_elapsed;

      //std::vector<pass_details_t> d_passlist;

      //make pointer
//      std::vector<pass_details_t>
//      generate_passlist (SGP4& sgp4, const DateTime& start_time,
//                         const DateTime& end_time, const int time_step);

      double
      find_max_elevation (Observer& observer, SGP4& sgp4, const DateTime& aos,
                          const DateTime& los);

      DateTime
      find_crossing_point_time (Observer& observer, SGP4& sgp4,
                                const DateTime& initial_time1,
                                const DateTime& initial_time2,
                                bool finding_aos);

    };

  } // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_TRACKER_H */

