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
#include <leo/satellite.h>
#include <iostream>

namespace gr
{
  namespace leo
  {

    satellite::satellite_sptr
    satellite::make (const std::string& tle_title, const std::string& tle_1,
                     const std::string& tle_2, const float freq_uplink,
                     const float freq_downlink,
                     generic_antenna::generic_antenna_sptr uplink_antenna,
                     generic_antenna::generic_antenna_sptr downlink_antenna)
    {
      return satellite::satellite_sptr (
          new satellite (tle_title, tle_1, tle_2, freq_uplink, freq_downlink,
                         uplink_antenna, downlink_antenna));
    }

    satellite::satellite (
        const std::string& tle_title, const std::string& tle_1,
        const std::string& tle_2, const float comm_freq_uplink,
        const float comm_freq_downlink,
        generic_antenna::generic_antenna_sptr uplink_antenna,
        generic_antenna::generic_antenna_sptr downlink_antenna) :
            d_tle_title (tle_title),
            d_tle_1 (tle_1),
            d_tle_2 (tle_2),
            d_comm_freq_uplink (comm_freq_uplink),
            d_comm_freq_downlink (comm_freq_downlink),
            d_uplink_antenna (uplink_antenna),
            d_downlink_antenna (downlink_antenna)
    {

      my_id = base_unique_id++;
    }

    satellite::~satellite ()
    {
    }

    int satellite::base_unique_id = 1;

    int
    satellite::unique_id ()
    {
      return my_id;
    }

    const float
    satellite::get_comm_freq_downlink () const
    {
      return d_comm_freq_downlink;
    }

    const float
    satellite::get_comm_freq_uplink () const
    {
      return d_comm_freq_uplink;
    }

    const std::string&
    satellite::get_tle_1 () const
    {
      return d_tle_1;
    }

    const std::string&
    satellite::get_tle_2 () const
    {
      return d_tle_2;
    }

    const std::string&
    satellite::get_tle_title () const
    {
      return d_tle_title;
    }

    generic_antenna::generic_antenna_sptr
    satellite::get_uplink_antenna ()
    {
      return d_uplink_antenna;
    }

    generic_antenna::generic_antenna_sptr
    satellite::get_downlink_antenna ()
    {
      return d_downlink_antenna;
    }

  } /* namespace leo */
} /* namespace gr */
