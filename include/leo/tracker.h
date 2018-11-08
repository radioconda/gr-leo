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

    /**
     * \brief Tracker represents an Earth ground station that observes an orbiting
     * satellite.
     *
     * Tracker holds all the information related to the observer such as the Geocentric
     * coordinates of the ground station and antenna setup. Also stores the observation
     * specific information such as the observed satellite, the observation timeframe
     * and the observation resolution in time.
     *
     * In addition, Tracker is responsible to appropriately call the API of <a href="https://www.danrw.com/sgp4">C++ SGP4</a>
     * for every calculation that is required to obtain orbit specific information
     * (i.e range from ground station, velocity etc).
     *
     */

    class LEO_API tracker
    {

    public:
      static int base_unique_id;

      int my_id;

      int
      unique_id ();

      typedef boost::shared_ptr<tracker> tracker_sptr;

      /*!
       * \param satellite_info Satellite object. Holds the information
       *        related to an orbiting satellite.
       * \param gs_lat The latitude of the ground station.
       * \param gs_lon The longitude of the ground station.
       * \param gs_alt The altitude of the ground station.
       * \param obs_start The starting time of the observation in ISO-8601 UTC.
       * \param obs_end The ending time of the observation in ISO-8601 UTC.
       * \param time_resolution_us The resolution of the observation in
       *        microseconds.
       * \param comm_freq_uplink The operating uplink frequency
       * \param comm_freq_downlink The operating downlink frequency
       * \param uplink_antenna A boost::shared_ptr to the uplink antenna
       * \param downlink_antenna A boost::shared_ptr to the downlink antenna
       *
       * \return a boost::shared_ptr to the constructed tracker object.
       */
      static tracker_sptr
      make (satellite::satellite_sptr satellite_info, const float gs_lat,
            const float gs_lon, const float gs_alt,
            const std::string& obs_start, const std::string& obs_end,
            const float time_resolution_us, const float comm_freq_uplink,
            const float comm_freq_downlink,
            generic_antenna::generic_antenna_sptr uplink_antenna,
            generic_antenna::generic_antenna_sptr downlink_antenna);

      ~tracker ();

      /*!
       * \brief The constructor of tracker class
       *
       * \param satellite_info Satellite object. Holds the information
       *        related to an orbiting satellite.
       * \param gs_lat The latitude of the ground station.
       * \param gs_lon The longitude of the ground station.
       * \param gs_alt The altitude of the ground station.
       * \param obs_start The starting time of the observation in ISO-8601 UTC.
       * \param obs_end The ending time of the observation in ISO-8601 UTC.
       * \param time_resolution_us The resolution of the observation in
       *        microseconds.
       * \param comm_freq_uplink The operating uplink frequency
       * \param comm_freq_downlink The operating downlink frequency
       * \param uplink_antenna A boost::shared_ptr to the uplink antenna
       * \param downlink_antenna A boost::shared_ptr to the downlink antenna
       *
       * \return a boost::shared_ptr to the constructed tracker object.
       */
      tracker (satellite::satellite_sptr satellite_info, const float gs_lat,
               const float gs_lon, const float gs_alt,
               const std::string& obs_start, const std::string& obs_end,
               const float time_resolution_us, const float comm_freq_uplink,
               const float comm_freq_downlink,
               generic_antenna::generic_antenna_sptr uplink_antenna,
               generic_antenna::generic_antenna_sptr downlink_antenna);

      /*!
       * \brief The constructor of tracker class
       *
       * \param tle_title The title segment of TLE
       * \param tle_1 The first line of TLE
       * \param tle_2 The second line of TLE
       * \param gs_lat The latitude of the ground station.
       * \param gs_lon The longitude of the ground station.
       * \param gs_alt The altitude of the ground station.
       * \param obs_start The starting time of the observation in ISO-8601 UTC.
       * \param obs_end The ending time of the observation in ISO-8601 UTC.
       *
       * \return a boost::shared_ptr to the constructed tracker object.
       */
      tracker (const std::string& tle_title, const std::string& tle_1,
               const std::string& tle_2, const float gs_lat, const float gs_lon,
               const float gs_alt, const std::string& obs_start,
               const std::string& obs_end);

      /*!
       * Generates a list of all the passes predictions for a specific triplet consisting
       * of a satellite, a ground station and an observation timeframe.
       * @return a std::vector of pass_details_t satellite passes.
       */
      std::vector<pass_details_t>
      generate_passlist (const int time_step);

      /*!
       * Get the observed satellite.
       * @return a boost::shared_ptr to the observed satellite.
       */
      satellite::satellite_sptr
      get_satellite_info ();

      /*!
       * Returns the range in kilometers between the observer and the satellite, at
       * the specific moment inside the observation.
       * @return a double representing the current range between the satellite and
       * the ground station.
       */
      double
      get_slant_range ();

      /*!
       * Returns the elevation of satellite in degrees at
       * the specific moment inside the observation.
       * @return a double representing the current elevation of the satellite.
       */
      double
      get_elevation_degrees ();

      /*!
       * Returns the elevation of satellite in radians at
       * the specific moment inside the observation.
       * @return a double representing the current elevation of the satellite.
       */
      double
      get_elevation_radians ();

      /*!
       * Returns the range rate of the observed satellite in kilometers/sec, at
       * the specific moment inside the observation.
       * @return a double representing the current range rate of the satellite.
       */
      double
      get_velocity ();

      /*!
       * Returns the elevation of the observed satellite in degrees, at
       * the specific moment inside the observation.
       * @return a double representing the current elevation of the satellite.
       */
      double
      get_current_elevation ();

      /*!
       * Returns the time resolution of the observation in microseconds.
       * @return a float representing the resolution in time of the observation.
       */
      float
      get_time_resolution_us ();

      /*!
       * Adds d_time_resolution_us microseconds to the elapsed time of the
       * observation.
       */
      void
      add_elapsed_time ();

      /*!
       * Checks whether the observation is over.
       * @return true if the observation is over,  false otherwise.
       */
      bool
      is_observation_over ();

      /*!
       * Returns the elapsed time of the observation.
       * @return a SGP4::DateTime representation of the elapsed time.
       */
      DateTime
      get_elapsed_time ();

      /*!
       * Returns the downlink frequency of the tracker's COMM system.
       * @return the frequency in Hz.
       */
      const float
      get_comm_freq_downlink () const;

      /*!
       * Returns the uplink frequency of the tracker's COMM system.
       * @return the frequency in Hz.
       */
      const float
      get_comm_freq_uplink () const;

      /*!
       * Returns the altitude of the ground station.
       * @return the altitude in km.
       */
      const float
      get_altitude () const;

      /*!
       * Returns the latitude of the ground station.
       * @return the latitude in degrees.
       */
      const float
      get_latitude () const;

      /*!
       * Returns the longitude of the ground station.
       * @return the longitude in degrees.
       */
      const float
      get_lontitude () const;

      /*!
       * Returns the antenna that is used from the tracker's uplink COMM system.
       * @return a boost::shared_ptr to the antenna.
       */
      generic_antenna::generic_antenna_sptr
      get_uplink_antenna ();

      /*!
       * Returns the antenna that is used from the tracker's downlink COMM system.
       * @return a boost::shared_ptr to the antenna.
       */
      generic_antenna::generic_antenna_sptr
      get_downlink_antenna ();

    private:
      std::vector<pass_details_t> d_passlist;
      Observer d_observer;
      satellite::satellite_sptr d_satellite;

      std::string d_tle_title;
      std::string d_tle_1;
      std::string d_tle_2;

      Tle d_tle;
      SGP4 d_sgp4;

      DateTime d_obs_start;
      DateTime d_obs_end;
      DateTime d_obs_elapsed;

      const float d_time_resolution_us;
      const float d_comm_freq_uplink;
      const float d_comm_freq_downlink;

      /**
       * The
       */
      const float d_gs_lat;
      const float d_gs_alt;
      const float d_gs_lon;

      generic_antenna::generic_antenna_sptr d_uplink_antenna;
      generic_antenna::generic_antenna_sptr d_downlink_antenna;

      /*!
       * Converts an ISO-8601 UTC timestamp into a libSGP4 DateTime object.
       */
      DateTime
      parse_ISO_8601_UTC (const std::string& datetime);

      /*!
       * Calculates the maximum elevation of a satellite for a specific
       * observation timeframe.
       */
      double
      find_max_elevation (Observer& observer, SGP4& sgp4, const DateTime& aos,
                          const DateTime& los);

      /*!
       * Estimates the timestamp that an orbiting satellite crosses the horizon.
       */
      DateTime
      find_crossing_point_time (Observer& observer, SGP4& sgp4,
                                const DateTime& initial_time1,
                                const DateTime& initial_time2,
                                bool finding_aos);

    };

  } // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_TRACKER_H */

