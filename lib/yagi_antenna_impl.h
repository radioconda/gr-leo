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

      /*!
       * \brief Class that represents a Yagi antenna.
       * \ingroup antenna
       * \details
       *
       * The yagi_antenna class extends the generic_antenna class
       * to simulate the behavior of a yagi antenna.
       */
      class LEO_API yagi_antenna_impl : public yagi_antenna
      {

      public:
        /*!
         * \brief The constructor of yagi_antenna class
         *
         * \param type The enumeration that defines the type of the antenna
         * \param frequency The frequency of the antenna in Hz
         * \param polarization The enumeration that defines the antenna
         * polarization
         * \param boom_length The length of the antenna boom in meters
         *
         */
        yagi_antenna_impl (uint8_t type, float frequency, int polarization,
                           float boom_length);

        ~yagi_antenna_impl ();

        /*!
         * \brief Get the gain of the yagi antenna. This is the implementation
         * of the parent's pure virtual function for the yagi antenna.
         * \return the gain in dBiC.
         */
        float
        get_gain ();

        /*!
         * \brief Get the beamwidth of the yagi antenna. This is the implementation
         * of the parent's pure virtual function for the yagi antenna.
         * \return the beamwidth
         */
        float
        get_beamwidth ();

      private:

        typedef std::tuple<float, float, float> yagi_preformance_t;

        /**
         * Data taken from ARPL antenna book.
         *
         * Τhe triplet refers to (boom length, elements number, maximum gain)
         */
        std::vector<yagi_preformance_t> d_yagi_performance
          { yagi_preformance_t (0.35, 3, 9.65), yagi_preformance_t (0.55, 4, 10.86),
            yagi_preformance_t (0.80, 5, 11.85), yagi_preformance_t (1.15, 6, 12.45),
            yagi_preformance_t (1.45, 7, 13.45), yagi_preformance_t (1.80, 8, 14.05),
            yagi_preformance_t (2.10, 9, 14.40), yagi_preformance_t (2.45, 10, 15.25),
            yagi_preformance_t (2.80, 11, 15.95), yagi_preformance_t (3.15, 12, 16.30),
            yagi_preformance_t (3.55, 13, 16.95), yagi_preformance_t (4.00, 14, 17.45),
            yagi_preformance_t (4.40, 15, 18.15), yagi_preformance_t (4.75, 16, 18.65),
            yagi_preformance_t (5.20, 17, 19.35), yagi_preformance_t (5.55, 18, 19.85),
            yagi_preformance_t (6.00, 19, 20.25), yagi_preformance_t (6.50, 20, 20.75),
            yagi_preformance_t (7.00, 21, 21.35), yagi_preformance_t (7.50, 22, 21.65)};

        float d_boom_length;
        size_t d_optimum_elements;

        /*!
         * \brief Find the optimum number of elemets based on the lookup table d_yagi_performance
         * taken from the ARPL antenna book.
         *
         * \return the number of elements.
         */
        float
        find_optimum_elements ();

      };
    } // namespace antenna
  } // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_YAGI_ANTENNA_IMPL_H */

