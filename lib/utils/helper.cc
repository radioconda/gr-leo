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
      float
      parser_ITU_heatmap (std::string lat_file_path, std::string lon_file_path,
                          std::string heatmap_file_path, float lon, float lat)
      {
        float value = -1;

        size_t lon_idx = 0;
        size_t lat_idx = 0;
        size_t tmp_idx = 0;

        std::ifstream lon_file (lon_file_path);
        std::string line;
        std::getline (lon_file, line);

        boost::tokenizer<separator_type> tokenizer (line, separator_type (" "));
        auto it = tokenizer.begin ();
        while (it != tokenizer.end ()) {
          float val = std::atof ((*it++).c_str ());
          if (val == lon) {
            break;
          }
          /**
           * TODO: Fix the case that lon data is descending
           */
          else if (val > lon) {
            lon_idx--;
            break;
          }
          lon_idx++;
        }

        std::ifstream file_lat (lat_file_path);
        while (std::getline (file_lat, line)) {
          boost::tokenizer<separator_type> tokenizer (line,
                                                      separator_type ("\t"));
          auto it = tokenizer.begin ();
          float val = std::atof ((*it).c_str ());
          if (val == lat) {
            break;
          }
          /**
           * TODO: Fix the case that lat data is ascending
           */
          else if (val < lat) {
            lat_idx--;
            break;
          }
          lat_idx++;
        }

        std::ifstream file_heatmap (heatmap_file_path);
        while (std::getline (file_heatmap, line)) {
          if (tmp_idx == lat_idx) {
            tmp_idx = 0;
            boost::tokenizer<separator_type> tokenizer (line,
                                                        separator_type ("\t"));
            auto it = tokenizer.begin ();
            for (boost::tokenizer<separator_type>::iterator it =
                tokenizer.begin (); it != tokenizer.end (); ++it) {
              if (tmp_idx == lon_idx) {
                float tmp = std::atof ((*it).c_str ());
                value = tmp;
                break;
              }
              tmp_idx++;
            }
          }
          if (value > 0) {
            break;
          }
          tmp_idx++;
        }
        return value;
      }
    } /* utils */
  } /* namespace leo */
} /* namespace gr */

