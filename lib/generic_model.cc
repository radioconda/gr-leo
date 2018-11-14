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

namespace gr
{
  namespace leo
  {

    generic_model::generic_model (std::string name,
                                  tracker::tracker_sptr tracker,
                                  const uint8_t mode) :
            d_name (name),
            d_mode (mode),
            d_tracker (tracker)
    {
      my_id = base_unique_id++;
    }

    generic_model::~generic_model ()
    {
    }

    tracker::tracker_sptr
    generic_model::get_tracker ()
    {
      return d_tracker;
    }

    float
    generic_model::get_frequency ()
    {
      if (d_mode == UPLINK) {
        return d_tracker->get_comm_freq_uplink ();
      }
      else if (d_mode == DOWNLINK) {
        return d_tracker->get_comm_freq_downlink ();
      }
      else {
        throw std::runtime_error ("Invalid transmission mode");
      }
    }

    uint8_t
    generic_model::get_polarization ()
    {
      if (d_mode == UPLINK) {
        return d_tracker->get_uplink_antenna ()->get_polarization ();
      }
      else if (d_mode == DOWNLINK) {
        return d_tracker->get_downlink_antenna ()->get_polarization ();
      }
      else {
        throw std::runtime_error ("Invalid transmission mode");
      }
    }

    float
    generic_model::get_tracker_antenna_gain ()
    {
      if (d_mode == UPLINK) {
        return d_tracker->get_uplink_antenna ()->get_gain ();
      }
      else if (d_mode == DOWNLINK) {
        return d_tracker->get_downlink_antenna ()->get_gain ();
      }
      else {
        throw std::runtime_error ("Invalid transmission mode");
      }
    }

    generic_antenna::generic_antenna_sptr
    generic_model::get_tracker_antenna ()
    {
      if (d_mode == UPLINK) {
        return d_tracker->get_uplink_antenna ();
      }
      else if (d_mode == DOWNLINK) {
        return d_tracker->get_downlink_antenna ();
      }
      else {
        throw std::runtime_error ("Invalid transmission mode");
      }
    }

    float
    generic_model::get_satellite_antenna_gain ()
    {
      if (d_mode == UPLINK) {
        return d_tracker->get_satellite_info ()->get_uplink_antenna ()->get_gain ();
      }
      else if (d_mode == DOWNLINK) {
        return d_tracker->get_satellite_info ()->get_downlink_antenna ()->get_gain ();
      }
      else {
        throw std::runtime_error ("Invalid transmission mode");
      }
    }

    generic_antenna::generic_antenna_sptr
    generic_model::get_satellite_antenna ()
    {
      if (d_mode == UPLINK) {
        return d_tracker->get_satellite_info ()->get_uplink_antenna ();
      }
      else if (d_mode == DOWNLINK) {
        return d_tracker->get_satellite_info ()->get_downlink_antenna ();
      }
      else {
        throw std::runtime_error ("Invalid transmission mode");
      }
    }

    int generic_model::base_unique_id = 1;

    int
    generic_model::unique_id ()
    {
      return my_id;
    }

    std::string
    generic_model::get_csv_log ()
    {
      return d_csv_log;
    }

    void
    generic_model::orbit_update ()
    {
      float elevation_radians = d_tracker->get_elevation_radians ();
      double range = d_tracker->get_slant_range ();
      uint8_t polarization = get_polarization ();

      generic_attenuation::set_elevation_angle (elevation_radians);
      generic_attenuation::set_frequency (get_frequency ());
      generic_attenuation::set_polarization (polarization);
      generic_attenuation::set_slant_range (range);
    }

  } /* namespace leo */
} /* namespace gr */
