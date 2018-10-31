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
#include <leo/utils/helper.h>
#include <leo/log.h>

typedef boost::char_separator<char> separator_type;

namespace gr
{
  namespace leo
  {
    namespace utils
    {
      /**
       *
       */
      float
      parser_ITU_heatmap (std::string lat_file_path, std::string lon_file_path,
                          std::string heatmap_file_path, float lon, float lat)
      {
        float value = -1;

        size_t lon_idx = 0;
        size_t lat_idx = 0;
        size_t tmp_idx = 0;
        size_t middle_idx;
        bool reversed = false;
        float tmp;

        std::vector<float> coord;

        std::string line;
        boost::regex pat ("[^\\s\\n]+");
        boost::regex pattern (pat);

        /**
         * Handle Longitude
         */
        std::ifstream lon_file (lon_file_path);
        std::getline (lon_file, line);

        boost::sregex_iterator it (line.begin (), line.end (), pattern);
        boost::sregex_iterator end;

        for (; it != end; ++it) {
          coord.push_back (std::atof (it->str ().c_str ()));
        }

        // Convert ITU data to follow (-180, 180) scheme
        if (*max_element (coord.begin (), coord.end ()) == 360) {
          for (size_t t = 0; t < coord.size (); t++) {
            coord[t] -= 180;
          }
        }
        if (!std::is_sorted (coord.begin (), coord.end ())) {
          std::reverse (coord.begin (), coord.end ());
          reversed = true;
        }
        lon_idx = std::distance (
            coord.begin (),
            std::lower_bound (coord.begin (), coord.end () - 1, lon));
        if (reversed) {
          middle_idx = (coord.size () - 1) / 2;
          lon_idx =
              (lon_idx >= middle_idx) ?
                  lon_idx - 2 * (std::fabs (middle_idx - lon_idx)) :
                  lon_idx + 2 * (std::fabs (middle_idx - lon_idx));
        }
        reversed = false;

        /**
         * Handle Latitude
         */
        std::ifstream lat_file (lat_file_path);
        coord.clear ();
        while (std::getline (lat_file, line)) {
          boost::sregex_iterator it_lat (line.begin (), line.end (), pattern);
          tmp = std::atof (it_lat->str ().c_str ());
          coord.push_back (tmp);
        }

        // Convert ITU data to follow (-90, 90) scheme
        if (*max_element (coord.begin (), coord.end ()) == 180) {
          for (size_t t = 0; t < coord.size (); t++) {
            coord[t] -= 90;
          }
        }
        if (!std::is_sorted (coord.begin (), coord.end ())) {
          std::reverse (coord.begin (), coord.end ());
          reversed = true;
        }
        lat_idx = std::distance (
            coord.begin (),
            std::lower_bound (coord.begin (), coord.end () - 1, lat));
        if (reversed) {
          middle_idx = (coord.size () - 1) / 2;
          lat_idx =
              (lat_idx >= middle_idx) ?
                  lat_idx - 2 * (lat_idx - middle_idx) :
                  lat_idx + 2 * (middle_idx - lat_idx);
        }

        /**
         * Handle Latitude
         */
        std::ifstream heatmap_file (heatmap_file_path);
        coord.clear ();
        while (std::getline (heatmap_file, line)) {
          if (tmp_idx == lat_idx) {
            tmp_idx = 0;
            boost::sregex_iterator it_lat (line.begin (), line.end (), pattern);
            break;
          }
          tmp_idx++;
        }
        boost::sregex_iterator it_heat (line.begin (), line.end (), pattern);
        for (; it_heat != end; ++it_heat) {
          if (tmp_idx == lon_idx) {
            value = std::atof (it_heat->str ().c_str ());
            break;
          }
          tmp_idx++;
        }

        return value;

      }

    } /* utils */
  } /* namespace leo */
} /* namespace gr */

