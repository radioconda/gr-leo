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

#ifndef INCLUDED_LEO_YAGI_ANTENNA_IMPL_H
#define INCLUDED_LEO_YAGI_ANTENNA_IMPL_H

#include "../include/leo/yagi_antenna.h"
#include <vector>

namespace gr
{
  namespace leo
  {
    namespace antenna
    {
      typedef std::tuple<float, float, float> yagi_preformance_t;

      class LEO_API yagi_antenna_impl : public yagi_antenna
      {

      public:
        yagi_antenna_impl (uint8_t type, float frequency, int polarization, float boom_length);

        ~yagi_antenna_impl ();

        float
        get_gain();

        float
        get_beamwidth();

      private:
        /**
         * Data taken from ARPL antenna book
         */
        std::vector<yagi_preformance_t> d_yagi_performance {
                  yagi_preformance_t(0.35, 3, 9.65),
                  yagi_preformance_t(0.55, 4, 10.86),
                  yagi_preformance_t(0.80, 5, 11.85),
                  yagi_preformance_t(1.15, 6, 12.45),
                  yagi_preformance_t(1.45, 7, 13.45),
                  yagi_preformance_t(1.80, 8, 14.05),
                  yagi_preformance_t(2.10, 9, 14.40),
                  yagi_preformance_t(2.45, 10, 15.25),
                  yagi_preformance_t(2.80, 11, 15.95),
                  yagi_preformance_t(3.15, 12, 16.30),
                  yagi_preformance_t(3.55, 13, 16.95),
                  yagi_preformance_t(4.00, 14, 17.45),
                  yagi_preformance_t(4.40, 15, 18.15),
                  yagi_preformance_t(4.75, 16, 18.65),
                  yagi_preformance_t(5.20, 17, 19.35),
                  yagi_preformance_t(5.55, 18, 19.85),
                  yagi_preformance_t(6.00, 19, 20.25),
                  yagi_preformance_t(6.50, 20, 20.75),
                  yagi_preformance_t(7.00, 21, 21.35),
                  yagi_preformance_t(7.50, 22, 21.65),
              };

        float d_boom_length;
        size_t d_optimum_elements;

        float
        find_optimum_elements();

      };
    } // namespace antenna
  } // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_YAGI_ANTENNA_IMPL_H */

