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

#include <gnuradio/leo/api.h>
#include <gnuradio/leo/leo_types.h>
#include <gnuradio/leo/satellite.h>
#include <libsgp4/CoordTopocentric.h>
#include <libsgp4/CoordGeodetic.h>
#include <libsgp4/Observer.h>
#include <libsgp4/SGP4.h>
#include <iostream>
#include <vector>
#include <string>

namespace gr {
namespace leo {

/**
 * \brief Tracker represents an Earth ground station that observes an orbiting
 * satellite.
 * \ingroup tracker
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

class LEO_API tracker {

public:
  static int base_unique_id;

  int my_id;

  int
  unique_id();

  using tracker_sptr = std::shared_ptr<tracker>;

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
   * \param comm_freq_tx The operating TX frequency
   * \param comm_freq_rx The operating RX frequency
   * \param tx_power_dbm The TX power of the tracker in dBm
   * \param tx_antenna A boost::shared_ptr to the TX antenna
   * \param rx_antenna A boost::shared_ptr to the RX antenna
   * \param noise_figure The noise figure of the tracker's receiver
   * \param noise_figure The effective noise temperature of the tracker's receiver
   * \param noise_figure The bandwidth of the tracker's receiver
   *
   * \return a boost::shared_ptr to the constructed tracker object.
   */
  static tracker_sptr
  make(satellite::satellite_sptr satellite_info, const double gs_lat,
       const double gs_lon, const double gs_alt,
       const std::string &obs_start, const std::string &obs_end,
       const double time_resolution_us, const double comm_freq_tx,
       const double comm_freq_rx,
       const double tx_power_dbm,
       generic_antenna::generic_antenna_sptr tx_antenna,
       generic_antenna::generic_antenna_sptr rx_antenna,
       const double noise_figure,
       const double noise_temp,
       const double rx_bw);

  ~tracker();

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
   * \param comm_freq_tx The operating TX frequency
   * \param comm_freq_rx The operating RX frequency
   * \param tx_power_dbm The TX power of the tracker in dBm
   * \param tx_antenna A boost::shared_ptr to the TX antenna
   * \param rx_antenna A boost::shared_ptr to the RX antenna
   * \param noise_figure The noise figure of the tracker's receiver
   * \param noise_figure The effective noise temperature of the tracker's receiver
   * \param noise_figure The bandwidth of the tracker's receiver
   *
   * \return a boost::shared_ptr to the constructed tracker object.
   */
  tracker(satellite::satellite_sptr satellite_info, const double gs_lat,
          const double gs_lon, const double gs_alt,
          const std::string &obs_start, const std::string &obs_end,
          const double time_resolution_us, const double comm_freq_tx,
          const double comm_freq_rx,
          const double tx_power_dbm,
          generic_antenna::generic_antenna_sptr tx_antenna,
          generic_antenna::generic_antenna_sptr rx_antenna,
          const double noise_figure,
          const double noise_temp,
          const double rx_bw);

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
  tracker(const std::string &tle_title, const std::string &tle_1,
          const std::string &tle_2, const double gs_lat, const double gs_lon,
          const double gs_alt, const std::string &obs_start,
          const std::string &obs_end);

  /*!
   * Generates a list of all the passes predictions for a specific triplet consisting
   * of a satellite, a ground station and an observation timeframe.
   * @return a std::vector of pass_details_t satellite passes.
   */
  std::vector<pass_details_t>
  generate_passlist(const int time_step);

  /*!
   * Get the observed satellite.
   * @return a boost::shared_ptr to the observed satellite.
   */
  satellite::satellite_sptr
  get_satellite_info();

  /*!
   * Returns the range in kilometers between the observer and the satellite, at
   * the specific moment inside the observation.
   * @return a double representing the current range between the satellite and
   * the ground station.
   */
  double
  get_slant_range();

  /*!
   * Returns the elevation of satellite in degrees at
   * the specific moment inside the observation.
   * @return a double representing the current elevation of the satellite.
   */
  double
  get_elevation_degrees();

  /*!
   * Returns the elevation of satellite in radians at
   * the specific moment inside the observation.
   * @return a double representing the current elevation of the satellite.
   */
  double
  get_elevation_radians();

  /*!
   * Returns the range rate of the observed satellite in kilometers/sec, at
   * the specific moment inside the observation.
   * @return a double representing the current range rate of the satellite.
   */
  double
  get_velocity();


  /*!
   * Returns the time resolution of the observation in microseconds.
   * @return a double representing the resolution in time of the observation.
   */
  double
  get_time_resolution_us();

  /*!
   * Advances the simulation absolute timing by \ref us microseconds
   * @param us microseconds to advance the absolute timing of the
   * simulation
   */
  void
  advance_time(double us);

  /*!
   * Checks whether the observation is over.
   * @return true if the observation is over,  false otherwise.
   */
  bool
  is_observation_over();

  /*!
   * Returns the elapsed time of the observation.
   * @return a libsgp4::DateTime representation of the elapsed time.
   */
  libsgp4::DateTime
  get_elapsed_time();

  /*!
   * Returns the RX frequency of the tracker's COMM system.
   * @return the frequency in Hz.
   */
  const double
  get_comm_freq_rx() const;

  /*!
   * Returns the TX frequency of the tracker's COMM system.
   * @return the frequency in Hz.
   */
  const double
  get_comm_freq_tx() const;

  /*!
   * Returns the altitude of the ground station.
   * @return the altitude in km.
   */
  const double
  get_altitude() const;

  /*!
   * Returns the latitude of the ground station.
   * @return the latitude in degrees.
   */
  const double
  get_latitude() const;

  /*!
   * Returns the longitude of the ground station.
   * @return the longitude in degrees.
   */
  const double
  get_lontitude() const;

  /*!
   * Returns the antenna that is used from the tracker's TX COMM system.
   * @return a boost::shared_ptr to the antenna.
   */
  generic_antenna::generic_antenna_sptr
  get_tx_antenna();

  /*!
   * Returns the antenna that is used from the tracker's RX COMM system.
   * @return a boost::shared_ptr to the antenna.
   */
  generic_antenna::generic_antenna_sptr
  get_rx_antenna();

  /*!
   * Returns the TX power of the satellite's COMM system.
   * @return the TX power in dBm.
   */
  const double
  get_tx_power_dbm() const;

  /*!
   * Returns the noise figure of the tracker's COMM system.
   * @return the noise figure in dB.
   */
  const double
  get_noise_figure() const;

  /*!
  * Returns the effective noise temperature of the tracker's COMM system.
  * @return the noise temperature in K.
  */
  const double
  get_noise_temperature() const;

  /*!
   * Returns the receiver bandwidth of the tracker's COMM system.
   * @return the bandwidth in Hz.
   */
  const double
  get_rx_bandwidth() const;


private:
  std::vector<pass_details_t> d_passlist;
  libsgp4::Observer d_observer;
  satellite::satellite_sptr d_satellite;

  std::string d_tle_title;
  std::string d_tle_1;
  std::string d_tle_2;

  libsgp4::Tle d_tle;
  libsgp4::SGP4 d_sgp4;

  libsgp4::DateTime d_obs_start;
  libsgp4::DateTime d_obs_end;
  libsgp4::DateTime d_obs_elapsed;

  const double d_time_resolution_us;
  const double d_comm_freq_tx;
  const double d_comm_freq_rx;
  const double d_tx_power_dbm;
  const double d_noise_figure;
  const double d_noise_temp;
  const double d_rx_bw;

  /**
   * The coordinates of the ground station.
   */
  const double d_gs_lat;
  const double d_gs_alt;
  const double d_gs_lon;

  generic_antenna::generic_antenna_sptr d_tx_antenna;
  generic_antenna::generic_antenna_sptr d_rx_antenna;

  /*!
   * Converts an ISO-8601 UTC timestamp into a libSGP4 DateTime object.
   */
  libsgp4::DateTime
  parse_ISO_8601_UTC(const std::string &datetime);

  /*!
   * Calculates the maximum elevation of a satellite for a specific
   * observation timeframe.
   */
  double find_max_elevation(libsgp4::Observer& observer,
                            libsgp4::SGP4& sgp4,
                            const libsgp4::DateTime& aos,
                            const libsgp4::DateTime& los);

  /*!
   * Estimates the timestamp that an orbiting satellite crosses the horizon.
   */
  libsgp4::DateTime find_crossing_point_time(libsgp4::Observer& observer,
                                             libsgp4::SGP4& sgp4,
                                             const libsgp4::DateTime& initial_time1,
                                             const libsgp4::DateTime& initial_time2,
                                             bool finding_aos);
};

} // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_TRACKER_H */

