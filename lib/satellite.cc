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
#include <gnuradio/leo/satellite.h>
#include <iostream>

namespace gr {
namespace leo {

satellite::satellite_sptr
satellite::make(const std::string &tle_title, const std::string &tle_1,
                const std::string &tle_2, const double freq_tx,
                const double freq_rx,
                const double tx_power_dbm,
                generic_antenna::generic_antenna_sptr tx_antenna,
                generic_antenna::generic_antenna_sptr rx_antenna,
                const double noise_figure,
                const double noise_temp,
                const double rx_bw)
{
  return satellite::satellite_sptr(
           new satellite(tle_title, tle_1, tle_2, freq_tx, freq_rx,
                         tx_power_dbm, tx_antenna, rx_antenna, noise_figure,
                         noise_temp, rx_bw));
}

satellite::satellite(
  const std::string &tle_title, const std::string &tle_1,
  const std::string &tle_2, const double comm_freq_tx,
  const double comm_freq_rx,
  const double tx_power_dbm,
  generic_antenna::generic_antenna_sptr tx_antenna,
  generic_antenna::generic_antenna_sptr rx_antenna,
  const double noise_figure,
  const double noise_temp,
  const double rx_bw) :
  d_tle_title(tle_title),
  d_tle_1(tle_1),
  d_tle_2(tle_2),
  d_comm_freq_tx(comm_freq_tx),
  d_comm_freq_rx(comm_freq_rx),
  d_tx_antenna(tx_antenna),
  d_rx_antenna(rx_antenna),
  d_tx_power_dbm(tx_power_dbm),
  d_noise_figure(noise_figure),
  d_noise_temp(noise_temp),
  d_rx_bw(rx_bw)
{

  my_id = base_unique_id++;
}

satellite::~satellite()
{
}

int satellite::base_unique_id = 1;

int
satellite::unique_id()
{
  return my_id;
}

const double
satellite::get_comm_freq_rx() const
{
  return d_comm_freq_rx;
}

const double
satellite::get_comm_freq_tx() const
{
  return d_comm_freq_tx;
}

const std::string &
satellite::get_tle_1() const
{
  return d_tle_1;
}

const std::string &
satellite::get_tle_2() const
{
  return d_tle_2;
}

const std::string &
satellite::get_tle_title() const
{
  return d_tle_title;
}

generic_antenna::generic_antenna_sptr
satellite::get_tx_antenna()
{
  return d_tx_antenna;
}

generic_antenna::generic_antenna_sptr
satellite::get_rx_antenna()
{
  return d_rx_antenna;
}

const double
satellite::get_tx_power_dbm() const
{
  return d_tx_power_dbm;
}

const double
satellite::get_noise_figure() const
{
  return d_noise_figure;
}

const double
satellite::get_noise_temperature() const
{
  return d_noise_temp;
}

const double
satellite::get_rx_bandwidth() const
{
  return d_rx_bw;
}


} /* namespace leo */
} /* namespace gr */
