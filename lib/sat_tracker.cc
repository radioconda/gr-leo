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
#include <leo/sat_tracker.h>

namespace gr
{
  namespace leo
  {

    sat_tracker::sat_tracker (const std::string& tle_title,
                              const std::string& tle_1,
                              const std::string& tle_2, const float gs_lat,
                              const float gs_lon, const float gs_alt,
                              datetime obs_start,
                              datetime obs_end) :
            d_observer (gs_lat, gs_lon, gs_alt),
            d_tle (Tle (tle_title, tle_1, tle_2)),
            d_sgp4 (d_tle)
    {
      d_obs_start = DateTime (obs_start.get_year (), obs_start.get_month (),
                              obs_start.get_day (), obs_start.get_hour (),
                              obs_start.get_minute (), obs_start.get_second ());

      d_obs_end = DateTime (obs_end.get_year (), obs_end.get_month (),
                            obs_end.get_day (), obs_end.get_hour (),
                            obs_end.get_minute (), obs_end.get_second ());

      d_passlist = generate_passlist (d_sgp4, d_obs_start, d_obs_end, 180);
      if (d_passlist.begin () == d_passlist.end ()) {
        std::cout << "No passes found" << std::endl;
      }
      else {
        std::stringstream ss;

        ss << std::right << std::setprecision (1) << std::fixed;

        std::vector<pass_details_t>::const_iterator itr = d_passlist.begin ();
        do {
          ss << "AOS: " << itr->aos << ", LOS: " << itr->los << ", Max El: "
              << std::setw (4) << Util::RadiansToDegrees (itr->max_elevation)
              << ", Duration: " << (itr->los - itr->aos) << std::endl;
        }
        while (++itr != d_passlist.end ());

        std::cout << ss.str ();
      }
    }

    sat_tracker::~sat_tracker ()
    {
    }

    double
    sat_tracker::FindMaxElevation (Observer& observer, SGP4& sgp4,
                                   const DateTime& aos, const DateTime& los)
    {

      bool running;

      double time_step = (los - aos).TotalSeconds () / 9.0;
      DateTime current_time (aos); //! current time
      DateTime time1 (aos); //! start time of search period
      DateTime time2 (los); //! end time of search period
      double max_elevation; //! max elevation

      running = true;

      do {
        running = true;
        max_elevation = -99999999999999.0;
        while (running && current_time < time2) {
          /*
           * find position
           */
          Eci eci = sgp4.FindPosition (current_time);
          CoordTopocentric topo = observer.GetLookAngle (eci);

          if (topo.elevation > max_elevation) {
            /*
             * still going up
             */
            max_elevation = topo.elevation;
            /*
             * move time along
             */
            current_time = current_time.AddSeconds (time_step);
            if (current_time > time2) {
              /*
               * dont go past end time
               */
              current_time = time2;
            }
          }
          else {
            /*
             * stop
             */
            running = false;
          }
        }

        /*
         * make start time to 2 time steps back
         */
        time1 = current_time.AddSeconds (-2.0 * time_step);
        /*
         * make end time to current time
         */
        time2 = current_time;
        /*
         * current time to start time
         */
        current_time = time1;
        /*
         * recalculate time step
         */
        time_step = (time2 - time1).TotalSeconds () / 9.0;
      }
      while (time_step > 1.0);

      return max_elevation;
    }

    DateTime
    sat_tracker::FindCrossingPoint (Observer& observer, SGP4& sgp4,
                                    const DateTime& initial_time1,
                                    const DateTime& initial_time2,
                                    bool finding_aos)
    {
      bool running;
      int cnt;

      DateTime time1 (initial_time1);
      DateTime time2 (initial_time2);
      DateTime middle_time;

      running = true;
      cnt = 0;
      while (running && cnt++ < 16) {
        middle_time = time1.AddSeconds ((time2 - time1).TotalSeconds () / 2.0);
        /*
         * calculate satellite position
         */
        Eci eci = sgp4.FindPosition (middle_time);
        CoordTopocentric topo = observer.GetLookAngle (eci);

        if (topo.elevation > 0.0) {
          /*
           * satellite above horizon
           */
          if (finding_aos) {
            time2 = middle_time;
          }
          else {
            time1 = middle_time;
          }
        }
        else {
          if (finding_aos) {
            time1 = middle_time;
          }
          else {
            time2 = middle_time;
          }
        }

        if ((time2 - time1).TotalSeconds () < 1.0) {
          /*
           * two times are within a second, stop
           */
          running = false;
          /*
           * remove microseconds
           */
          int us = middle_time.Microsecond ();
          middle_time = middle_time.AddMicroseconds (-us);
          /*
           * step back into the pass by 1 second
           */
          middle_time = middle_time.AddSeconds (finding_aos ? 1 : -1);
        }
      }

      /*
       * go back/forward 1second until below the horizon
       */
      running = true;
      cnt = 0;
      while (running && cnt++ < 6) {
        Eci eci = sgp4.FindPosition (middle_time);
        CoordTopocentric topo = observer.GetLookAngle (eci);
        if (topo.elevation > 0) {
          middle_time = middle_time.AddSeconds (finding_aos ? -1 : 1);
        }
        else {
          running = false;
        }
      }

      return middle_time;
    }

    std::vector<pass_details_t>
    sat_tracker::generate_passlist (SGP4& sgp4, const DateTime& start_time,
                                    const DateTime& end_time,
                                    const int time_step)
    {
      pass_details_t pd;
      DateTime aos_time;
      DateTime los_time;

      bool found_aos = false;

      DateTime previous_time (start_time);
      DateTime current_time (start_time);

      while (current_time < end_time) {
        bool end_of_pass = false;

        /*
         * calculate satellite position
         */
        Eci eci = d_sgp4.FindPosition (current_time);
        CoordTopocentric topo = d_observer.GetLookAngle (eci);

        if (!found_aos && topo.elevation > 0.0) {
          /*
           * aos hasnt occured yet, but the satellite is now above horizon
           * this must have occured within the last time_step
           */
          if (start_time == current_time) {
            /*
             * satellite was already above the horizon at the start,
             * so use the start time
             */
            aos_time = start_time;
          }
          else {
            /*
             * find the point at which the satellite crossed the horizon
             */
            aos_time = FindCrossingPoint (d_observer, d_sgp4, previous_time,
                                          current_time, true);
          }
          found_aos = true;
        }
        else if (found_aos && topo.elevation < 0.0) {
          found_aos = false;
          /*
           * end of pass, so move along more than time_step
           */
          end_of_pass = true;
          /*
           * already have the aos, but now the satellite is below the horizon,
           * so find the los
           */
          los_time = FindCrossingPoint (d_observer, d_sgp4, previous_time,
                                        current_time, false);

          pd.aos = aos_time;
          pd.los = los_time;
          pd.max_elevation = FindMaxElevation (d_observer, d_sgp4, aos_time,
                                               los_time);

          d_passlist.push_back (pd);
        }

        /*
         * save current time
         */
        previous_time = current_time;

        if (end_of_pass) {
          /*
           * at the end of the pass move the time along by 30mins
           */
          current_time = current_time + TimeSpan (0, 30, 0);
        }
        else {
          /*
           * move the time along by the time step value
           */
          current_time = current_time + TimeSpan (0, 0, time_step);
        }

        if (current_time > end_time) {
          /*
           * dont go past end time
           */
          current_time = end_time;
        }
      };

      if (found_aos) {
        /*
         * satellite still above horizon at end of search period, so use end
         * time as los
         */
        pass_details_t pd;
        pd.aos = aos_time;
        pd.los = end_time;
        pd.max_elevation = FindMaxElevation (d_observer, d_sgp4, aos_time,
                                             end_time);

        d_passlist.push_back (pd);
      }

      return d_passlist;
    }

  } /* namespace leo */
} /* namespace gr */

