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
#include <leo/tracker.h>
#include <chrono>
#include <ctime>

namespace gr
{
  namespace leo
  {

    tracker::tracker_sptr
    tracker::make (satellite::satellite_sptr satellite_info, const float gs_lat,
                   const float gs_lon, const float gs_alt,
                   const std::string& obs_start, const std::string& obs_end,
                   const float time_resolution_us, const float comm_freq_uplink,
                   const float comm_freq_downlink,
                   generic_antenna::generic_antenna_sptr uplink_antenna,
                   generic_antenna::generic_antenna_sptr downlink_antenna,
                   const std::string& name)
    {
      return tracker::tracker_sptr (
          new tracker (satellite_info, gs_lat, gs_lon, gs_alt, obs_start,
                       obs_end, time_resolution_us, comm_freq_uplink,
                       comm_freq_downlink, uplink_antenna, downlink_antenna,
                       name));
    }

    /**
     * Construct the Tracker.
     *
     * @param satellite_info the observed satellite.
     *
     * @param gs_lat the latitude of the ground station in degrees.
     *
     * @param gs_lon the longitude of the ground station in degrees.
     *
     * @param gs_alt the altitude of the ground station in degrees.
     *
     * @param obs_start the starting timestamp of the observation in ISO-8601 UTC string format.
     *
     * @param obs_end the ending timestamp of the observation in ISO-8601 UTC string format.
     *
     * @param time_resolution_us the time resolution of the observation in microseconds. This quantity
     * defines the interval between every orbit-related calculation for the observed satellite.
     */
    tracker::tracker (satellite::satellite_sptr satellite_info,
                      const float gs_lat, const float gs_lon,
                      const float gs_alt, const std::string& obs_start,
                      const std::string& obs_end,
                      const float time_resolution_us,
                      const float comm_freq_uplink,
                      const float comm_freq_downlink,
                      generic_antenna::generic_antenna_sptr uplink_antenna,
                      generic_antenna::generic_antenna_sptr downlink_antenna,
                      const std::string& name) :
            d_time_resolution_us (time_resolution_us),
            d_observer (gs_lat, gs_lon, gs_alt),
            d_satellite (satellite_info),
            d_tle (
                Tle (d_satellite->get_tle_title (), d_satellite->get_tle_1 (),
                     d_satellite->get_tle_2 ())),
            d_sgp4 (d_tle),
            d_obs_start (parse_ISO_8601_UTC (obs_start)),
            d_obs_end (parse_ISO_8601_UTC (obs_end)),
            d_obs_elapsed (d_obs_start),
            d_comm_freq_uplink (comm_freq_uplink),
            d_comm_freq_downlink (comm_freq_downlink),
            d_uplink_antenna (uplink_antenna),
            d_downlink_antenna (downlink_antenna)
    {
      if (d_obs_end <= d_obs_start) {
        throw std::runtime_error ("Invalid observation timeframe");
      }

      my_id = base_unique_id++;

      d_passlist = generate_passlist (d_observer, d_sgp4, d_obs_start,
                                      d_obs_end, 180);

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

    tracker::~tracker ()
    {
    }

    int tracker::base_unique_id = 1;

    int
    tracker::unique_id ()
    {
      return my_id;
    }

    satellite::satellite_sptr
    tracker::get_satellite_info ()
    {
      return d_satellite;
    }

    double
    tracker::find_max_elevation (Observer& observer, SGP4& sgp4,
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
    tracker::find_crossing_point_time (Observer& observer, SGP4& sgp4,
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

    std::vector<tracker::pass_details_t>
    tracker::generate_passlist (Observer& observer, SGP4& sgp4,
                                const DateTime& start_time,
                                const DateTime& end_time, const int time_step)
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
        Eci eci = sgp4.FindPosition (current_time);
        CoordTopocentric topo = observer.GetLookAngle (eci);

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
            aos_time = find_crossing_point_time (observer, sgp4, previous_time,
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
          los_time = find_crossing_point_time (observer, sgp4, previous_time,
                                               current_time, false);

          pd.aos = aos_time;
          pd.los = los_time;
          pd.max_elevation = find_max_elevation (observer, sgp4, aos_time,
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
        pd.max_elevation = find_max_elevation (observer, sgp4, aos_time,
                                               end_time);

        d_passlist.push_back (pd);
      }

      return d_passlist;
    }

    /**
     * Calculates the range, in kilometers, between the ground station and
     * the satellite, at a specific time instance of the observation timeframe.
     *
     * @return the range if the current elevation of the satellite is positive,
     * zero otherwise. Note that positive satellite elevation means that the
     * satellite is above the horizon and there is a line-of-sight with the observer.
     */
    double
    tracker::get_slant_range ()
    {
      double elevation;

      Eci eci = d_sgp4.FindPosition (get_elapsed_time ());
      CoordTopocentric topo = d_observer.GetLookAngle (eci);
      elevation = Util::RadiansToDegrees (topo.elevation);
      if (elevation < 0) {
        return 0;
      }
      else {
        return topo.range;
      }
    }

    double
    tracker::get_elevation_degrees ()
    {
      Eci eci = d_sgp4.FindPosition (get_elapsed_time ());
      CoordTopocentric topo = d_observer.GetLookAngle (eci);
      return Util::RadiansToDegrees (topo.elevation);
    }

    double
    tracker::get_elevation_radians ()
    {
      Eci eci = d_sgp4.FindPosition (get_elapsed_time ());
      CoordTopocentric topo = d_observer.GetLookAngle (eci);
      return topo.elevation;
    }

    double
    tracker::get_velocity ()
    {
      double elevation;

      Eci eci = d_sgp4.FindPosition (get_elapsed_time ());
      CoordTopocentric topo = d_observer.GetLookAngle (eci);

      return topo.range_rate;
    }

    double
    tracker::get_current_elevation ()
    {
      Eci eci = d_sgp4.FindPosition (get_elapsed_time ());
      CoordTopocentric topo = d_observer.GetLookAngle (eci);
      return Util::RadiansToDegrees (topo.elevation);
    }

    DateTime
    tracker::parse_ISO_8601_UTC (const std::string& datetime)
    {
      std::tm tm;
      strptime (datetime.c_str (), "%Y-%m-%dT%H:%M:%S", &tm);
      std::chrono::system_clock::time_point tp =
          std::chrono::system_clock::from_time_t (std::mktime (&tm));

      std::time_t t = std::chrono::system_clock::to_time_t (tp);
      std::tm utc_tm = *localtime (&t);

      return DateTime (utc_tm.tm_year + 1900, utc_tm.tm_mon + 1, utc_tm.tm_mday,
                       utc_tm.tm_hour, utc_tm.tm_min, utc_tm.tm_sec);
    }

    float
    tracker::get_time_resolution_us ()
    {
      return d_time_resolution_us;
    }

    const float
    tracker::get_comm_freq_downlink () const
    {
      return d_comm_freq_downlink;
    }

    const float
    tracker::get_comm_freq_uplink () const
    {
      return d_comm_freq_uplink;
    }

    generic_antenna::generic_antenna_sptr
    tracker::get_uplink_antenna ()
    {
      return d_uplink_antenna;
    }

    generic_antenna::generic_antenna_sptr
    tracker::get_downlink_antenna ()
    {
      return d_downlink_antenna;
    }

    void
    tracker::add_elapsed_time ()
    {
      d_obs_elapsed = d_obs_elapsed.AddTicks (d_time_resolution_us);
    }

    DateTime
    tracker::get_elapsed_time ()
    {
      return d_obs_elapsed;
    }

    bool
    tracker::is_observation_over ()
    {
      if (d_obs_elapsed >= d_obs_end) {
        return true;
      }
      else {
        return false;
      }
    }

  } /* namespace leo */
} /* namespace gr */

