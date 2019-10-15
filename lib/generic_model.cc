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

#include <leo/generic_model.h>
#include <iostream>

namespace gr {
namespace leo {

generic_model::generic_model(std::string name,
                             tracker::tracker_sptr tracker,
                             const uint8_t mode) :
  d_name(name),
  d_mode(mode),
  d_tracker(tracker)
{
  my_id = base_unique_id++;
}

generic_model::~generic_model()
{
}

tracker::tracker_sptr
generic_model::get_tracker()
{
  return d_tracker;
}

float
generic_model::get_frequency()
{
  float freq_rx;
  float freq_tx;

  if (d_mode == UPLINK) {
    freq_rx = d_tracker->get_satellite_info()->get_comm_freq_rx();
    freq_tx = d_tracker->get_comm_freq_tx();
  }
  else if (d_mode == DOWNLINK) {
    freq_tx = d_tracker->get_satellite_info()->get_comm_freq_tx();
    freq_rx = d_tracker->get_comm_freq_rx();
  }
  else {
    throw std::runtime_error("Invalid transmission mode");
  }

  if (freq_tx == freq_rx) {
    return freq_tx;
  }
  else {
    throw std::runtime_error("RX and TX frequencies not aligned");
  }
}

uint8_t
generic_model::get_polarization()
{
  if (d_mode == UPLINK) {
    return d_tracker->get_tx_antenna()->get_polarization();
  }
  else if (d_mode == DOWNLINK) {
    return d_tracker->get_rx_antenna()->get_polarization();
  }
  else {
    throw std::runtime_error("Invalid transmission mode");
  }
}

float
generic_model::get_tracker_antenna_gain()
{
  if (d_mode == UPLINK) {
    return d_tracker->get_tx_antenna()->get_gain();
  }
  else if (d_mode == DOWNLINK) {
    return d_tracker->get_rx_antenna()->get_gain();
  }
  else {
    throw std::runtime_error("Invalid transmission mode");
  }
}

generic_antenna::generic_antenna_sptr
generic_model::get_tracker_antenna()
{
  if (d_mode == UPLINK) {
    return d_tracker->get_tx_antenna();
  }
  else if (d_mode == DOWNLINK) {
    return d_tracker->get_rx_antenna();
  }
  else {
    throw std::runtime_error("Invalid transmission mode");
  }
}

float
generic_model::get_satellite_antenna_gain()
{
  if (d_mode == UPLINK) {
    return d_tracker->get_satellite_info()->get_rx_antenna()->get_gain();
  }
  else if (d_mode == DOWNLINK) {
    return d_tracker->get_satellite_info()->get_tx_antenna()->get_gain();
  }
  else {
    throw std::runtime_error("Invalid transmission mode");
  }
}

float
generic_model::get_tx_power_dbm()
{
  if (d_mode == UPLINK) {
    return d_tracker->get_tx_power_dbm();
  }
  else if (d_mode == DOWNLINK) {
    return d_tracker->get_satellite_info()->get_tx_power_dbm();
  }
  else {
    throw std::runtime_error("Invalid transmission mode");
  }
}

float
generic_model::get_noise_figure()
{
  if (d_mode == UPLINK) {
    return d_tracker->get_noise_figure();
  }
  else if (d_mode == DOWNLINK) {
    return d_tracker->get_satellite_info()->get_noise_figure();
  }
  else {
    throw std::runtime_error("Invalid transmission mode");
  }
}

float
generic_model::get_noise_temperature()
{
  if (d_mode == UPLINK) {
    return d_tracker->get_noise_temperature();
  }
  else if (d_mode == DOWNLINK) {
    return d_tracker->get_satellite_info()->get_noise_temperature();
  }
  else {
    throw std::runtime_error("Invalid transmission mode");
  }
}

float
generic_model::get_receiver_bandwidth()
{
  if (d_mode == UPLINK) {
    return d_tracker->get_rx_bandwidth();
  }
  else if (d_mode == DOWNLINK) {
    return d_tracker->get_satellite_info()->get_rx_bandwidth();
  }
  else {
    throw std::runtime_error("Invalid transmission mode");
  }
}

generic_antenna::generic_antenna_sptr
generic_model::get_satellite_antenna()
{
  if (d_mode == UPLINK) {
    return d_tracker->get_satellite_info()->get_rx_antenna();
  }
  else if (d_mode == DOWNLINK) {
    return d_tracker->get_satellite_info()->get_tx_antenna();
  }
  else {
    throw std::runtime_error("Invalid transmission mode");
  }
}

int generic_model::base_unique_id = 1;

int
generic_model::unique_id()
{
  return my_id;
}

std::string
generic_model::get_csv_log()
{
  return d_csv_log;
}

void
generic_model::orbit_update()
{
  float elevation_radians = d_tracker->get_elevation_radians();
  double range = d_tracker->get_slant_range();
  uint8_t polarization = get_polarization();

  generic_attenuation::set_elevation_angle(elevation_radians);
  generic_attenuation::set_frequency(get_frequency());
  generic_attenuation::set_polarization(polarization);
  generic_attenuation::set_slant_range(range);
}

} /* namespace leo */
} /* namespace gr */
