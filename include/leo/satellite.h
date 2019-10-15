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

#ifndef INCLUDED_LEO_SATELLITE_H
#define INCLUDED_LEO_SATELLITE_H

#include <leo/api.h>
#include <leo/generic_antenna.h>
#include <string>
#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>

namespace gr {
namespace leo {

/**
 * \brief Satellite represents a satellite in orbit.
 * \ingroup satellite
 * Satellite holds all the information related to the satellite orbiting the Earth, such the
 * Two-Line Element (TLE), the operating frequencies and the antenna setup.
 *
 * In order to parse the TLE and extract its information, the Satellite constructor
 * calls appropriately the API of <a href="https://www.danrw.com/sgp4">C++ SGP4</a>.
 */
class LEO_API satellite {
public:
  static int base_unique_id;

  int my_id;

  int
  unique_id();

public:
  typedef boost::shared_ptr<satellite> satellite_sptr;

  /*!
   * \param tle_title The title segment of TLE
   * \param tle_1 The first line of TLE
   * \param tle_2 The second line of TLE
   * \param comm_freq_tx The operating tx frequency
   * \param comm_freq_rx The operating rx frequency
   * \param tx_power_dbm The TX power of the satellite in dBm
   * \param tx_antenna A boost::shared_ptr to the tx antenna
   * \param rx_antenna A boost::shared_ptr to the rx antenna
   * \param noise_figure The noise figure of the satellite's receiver
   * \param noise_figure The effective noise temperature of the satellite's receiver
   * \param noise_figure The bandwidth of the satellite's receiver
   *
   * \return a boost::shared_ptr to the constructed tracker object.
   */
  static satellite_sptr
  make(const std::string &tle_title, const std::string &tle_1,
       const std::string &tle_2, const float comm_freq_tx,
       const float comm_freq_rx,
       const float tx_power_dbm,
       generic_antenna::generic_antenna_sptr tx_antenna,
       generic_antenna::generic_antenna_sptr rx_antenna,
       const float noise_figure,
       const float noise_temp,
       const float rx_bw);

  /*!
   * \brief The constructor of satellite class
   *
   * \param tle_title The title segment of TLE
   * \param tle_1 The first line of TLE
   * \param tle_2 The second line of TLE
   * \param comm_freq_tx The operating TX frequency
   * \param comm_freq_rx The operating RX frequency
   * \param tx_antenna A boost::shared_ptr to the TX antenna
   * \param rx_antenna A boost::shared_ptr to the RX antenna
   * \param tx_power_dbm The TX power of the satellite in dBm
   * \param noise_figure The noise figure of the satellite's receiver
   * \param noise_figure The effective noise temperature of the satellite's receiver
   * \param noise_figure The bandwidth of the satellite's receiver
   *
   * \return a boost::shared_ptr to the constructed tracker object.
   */
  satellite(const std::string &tle_title, const std::string &tle_1,
            const std::string &tle_2, const float comm_freq_tx,
            const float comm_freq_rx,
            const float tx_power_dbm,
            generic_antenna::generic_antenna_sptr tx_antenna,
            generic_antenna::generic_antenna_sptr rx_antenna,
            const float noise_figure,
            const float noise_temp,
            const float rx_bw);

  ~satellite();

  /*!
   * Returns the RX frequency of the satellite's COMM system.
   * @return the frequency in Hz.
   */
  const float
  get_comm_freq_rx() const;

  /*!
   * Returns the TX frequency of the satellite's COMM system.
   * @return the frequency in Hz.
   */
  const float
  get_comm_freq_tx() const;

  /*!
   * Returns the first line of the TLE.
   * @return a std::string representing the first line of the TLE
   */
  const std::string &
  get_tle_1() const;

  /*!
   * Returns the second line of the TLE.
   * @return a std::string representing the second line of the TLE
   */
  const std::string &
  get_tle_2() const;

  /*!
   * Returns the title segment of the TLE.
   * @return a std::string representing the TLE title
   */
  const std::string &
  get_tle_title() const;

  /*!
   * Returns the antenna that is used from the satellite's TX COMM system.
   * @return a boost::shared_ptr to the antenna.
   */
  generic_antenna::generic_antenna_sptr
  get_tx_antenna();

  /*!
   * Returns the antenna that is used from the satellite's RX COMM system.
   * @return a boost::shared_ptr to the antenna.
   */
  generic_antenna::generic_antenna_sptr
  get_rx_antenna();

  /*!
   * Returns the TX power of the satellite's COMM system.
   * @return the TX power in dBm.
   */
  const float
  get_tx_power_dbm() const;

  /*!
   * Returns the noise figure of the satellite's COMM system.
   * @return the noise figure in dB.
   */
  const float
  get_noise_figure() const;

  /*!
   * Returns the effective noise temperature of the satellite's COMM system.
   * @return the noise temperature in K.
   */
  const float
  get_noise_temperature() const;

  /*!
   * Returns the receiver bandwidth of the satellite's COMM system.
   * @return the bandwidth in Hz.
   */
  const float
  get_rx_bandwidth() const;

private:
  std::string d_tle_title;
  std::string d_tle_1;
  std::string d_tle_2;

  const float d_comm_freq_tx;
  const float d_comm_freq_rx;
  const float d_tx_power_dbm;
  const float d_noise_figure;
  const float d_noise_temp;
  const float d_rx_bw;

  generic_antenna::generic_antenna_sptr d_tx_antenna;
  generic_antenna::generic_antenna_sptr d_rx_antenna;

};

} // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_SATELLITE_H */

