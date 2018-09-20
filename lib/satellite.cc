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
#include <gnuradio/block_registry.h>
#include <leo/satellite.h>
#include <iostream>

namespace gr
{
  namespace leo
  {

    satellite::satellite_sptr
    satellite::make (const std::string& tle_title,
                     const std::string& tle_1, const std::string& tle_2,
                     const float freq_uplink, const float freq_downlink,
                     const std::string& name)
    {
      return satellite::satellite_sptr (
          new satellite (tle_title, tle_1, tle_2, freq_uplink,
                         freq_downlink, name));
    }

    satellite::satellite (const std::string& tle_title,
                          const std::string& tle_1, const std::string& tle_2,
                          const float freq_uplink, const float freq_downlink,
                          const std::string& name) :
            d_tle_title (tle_title),
            d_tle_1 (tle_1),
            d_tle_2 (tle_2),
            d_freq_uplink (freq_uplink),
            d_freq_downlink (freq_downlink)
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
    satellite::get_freq_downlink () const
    {
      return d_freq_downlink;
    }

    const float
    satellite::get_freq_uplink () const
    {
      return d_freq_uplink;
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


  } /* namespace leo */
} /* namespace gr */
