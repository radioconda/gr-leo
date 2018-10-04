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

namespace gr
{
  namespace leo
  {

    /**
     * @brief Satellite represents a satellite in orbit.
     *
     * Satellite holds all the information related to the satellite orbiting the Earth, such the
     * Two-Line Element (TLE) and the operating frequencies.
     *
     * In order to parse the TLE and extract its information, the Satellite constructor
     * calls appropriately the API of <a href="https://www.danrw.com/sgp4">C++ SGP4</a>.
     */
    class LEO_API satellite
    {
    public:
      static int base_unique_id;

      int my_id;

      int
      unique_id ();

    public:
      typedef boost::shared_ptr<satellite> satellite_sptr;

      static satellite_sptr
      make (const std::string& tle_title, const std::string& tle_1,
            const std::string& tle_2, const float comm_freq_uplink,
            const float comm_freq_downlink,
            generic_antenna::generic_antenna_sptr uplink_antenna,
            generic_antenna::generic_antenna_sptr downlink_antenna,
            const std::string& name);

      satellite (const std::string& tle_title, const std::string& tle_1,
                 const std::string& tle_2, const float comm_freq_uplink,
                 const float comm_freq_downlink,
                 generic_antenna::generic_antenna_sptr uplink_antenna,
                 generic_antenna::generic_antenna_sptr downlink_antenna,
                 const std::string& name);

      ~satellite ();

      const float
      get_comm_freq_downlink () const;

      const float
      get_comm_freq_uplink () const;

      const std::string&
      get_tle_1 () const;

      const std::string&
      get_tle_2 () const;

      const std::string&
      get_tle_title () const;

      generic_antenna::generic_antenna_sptr
      get_uplink_antenna ();

      generic_antenna::generic_antenna_sptr
      get_downlink_antenna ();

    private:
      std::string d_tle_title;
      std::string d_tle_1;
      std::string d_tle_2;

      const float d_comm_freq_uplink;
      const float d_comm_freq_downlink;

      generic_antenna::generic_antenna_sptr d_uplink_antenna;
      generic_antenna::generic_antenna_sptr d_downlink_antenna;

    };

  } // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_SATELLITE_H */

