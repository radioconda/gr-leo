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
#include <leo/atmosphere.h>
#include <cmath>

namespace gr
{
  namespace leo
  {

    /**
     *
     */
    atmosphere::atmosphere (float frequency) :
            d_frequency (frequency / 1e9)
    {
    }

    atmosphere::~atmosphere ()
    {
    }

    float
    atmosphere::geopotential_to_geometric (float alt)
    {
      return (6356.766 * alt) / (6356.766 - alt);
    }

    float
    atmosphere::geometric_to_geopotential (float alt)
    {
      return (6356.766 * alt) / (6356.766 + alt);
    }

    double
    atmosphere::get_temperature (float alt)
    {
      float geopotential_alt = geometric_to_geopotential (alt);
      double temperature = 0;
      /**
       * Troposphere
       */
      if (geopotential_alt >= 0 && geopotential_alt <= 11) {
        temperature = 288.15 - 6.5 * geopotential_alt;
      }
      /**
       * Tropopause
       */
      else if (geopotential_alt > 11 && geopotential_alt <= 20) {
        temperature = 216.65;
      }
      /**
       * Stratosphere
       */
      else if (geopotential_alt > 20 && geopotential_alt <= 32) {
        temperature = 216.65 + geopotential_alt - 20;
      }
      /**
       * Stratosphere
       */
      else if (geopotential_alt > 32 && geopotential_alt <= 47) {
        temperature = 228.65 + 2.8 * (geopotential_alt - 32);
      }
      /**
       * Stratopause
       */
      else if (geopotential_alt > 47 && geopotential_alt <= 51) {
        temperature = 270.65;
      }
      /**
       * Mesosphere
       */
      else if (geopotential_alt > 51 && geopotential_alt <= 71) {
        temperature = 270.65 - 2.8 * (geopotential_alt - 51);
      }
      /**
       * Mesosphere
       */
      else if (geopotential_alt > 71 && geopotential_alt <= 84.852) {
        temperature = 270.65 - 2.8 * (geopotential_alt - 51);
      }
      /**
       * Mesopause
       */
      else if (geopotential_alt > 86 && geopotential_alt <= 91) {
        temperature = 186.8673;
      }
      else if (alt > 91) {
        temperature = 263.1905
            - 76.3232 * std::pow (1 - std::pow ((alt - 91) / 19.9429, 2), 0.5);
      }
      return temperature;
    }

    double
    atmosphere::get_pressure (float alt)
    {
      float geopotential_alt = geometric_to_geopotential (alt);
      double pressure = 0;
      const double a0 = 95.571899;
      const double a1 = -4.011801;
      const double a2 = 6.424731e-2;
      const double a3 = -4.789660e-4;
      const double a4 = 1.340543e-6;

      /**
       * Troposphere
       */
      if (geopotential_alt >= 0 && geopotential_alt <= 11) {
        pressure = 1013.25
            * std::pow (288.15 / (288.15 - 6.5 * geopotential_alt),
                        -34.1632 / 6.5);
      }
      /**
       * Tropopause
       */
      else if (geopotential_alt > 11 && geopotential_alt <= 20) {
        pressure = 226.3226
            * std::exp (-34.1632 * (geopotential_alt - 11) / 216.65);
      }
      /**
       * Stratosphere
       */
      else if (geopotential_alt > 20 && geopotential_alt <= 32) {
        pressure = 54.74980
            * std::pow (216.65 / (216.65 + geopotential_alt - 20), -34.1632);
      }
      /**
       * Stratosphere
       */
      else if (geopotential_alt > 32 && geopotential_alt <= 47) {
        pressure = 8.680422
            * std::pow (228.65 / (228.65 + 2.8 * (geopotential_alt - 32)),
                        -34.1632 / 2.8);
      }
      /**
       * Stratopause
       */
      else if (geopotential_alt > 47 && geopotential_alt <= 51) {
        pressure = 1.109106
            * std::exp (-34.1632 * (geopotential_alt - 47) / 270.65);
      }
      /**
       * Mesosphere
       */
      else if (geopotential_alt > 51 && geopotential_alt <= 71) {
        pressure = 0.6694167
            * std::pow (270.65 / (270.65 - 2.8 * (geopotential_alt - 51)),
                        -34.1632 / 2.8);
      }
      /**
       * Mesosphere
       */
      else if (geopotential_alt > 71 && geopotential_alt <= 84.852) {
        pressure = 0.03956649
            * std::pow (214.65 / (214.65 - 2 * (geopotential_alt - 71)),
                        -34.1632 / 2);
      }
      /**
       * Mesopause
       */
      else if (geopotential_alt > 86) {
        pressure = std::exp (
            a0 + a1 * geopotential_alt + a2 * std::pow (geopotential_alt, 2)
                + a3 * std::pow (geopotential_alt, 3)
                + a4 * std::pow (geopotential_alt, 4));
      }
    }

    double
    atmosphere::get_water_vapour_pressure (float alt)
    {
      double rh = 7.5 * std::exp (-alt / 2);
      return (rh * get_temperature (alt)) / 216.7;
    }

//    float
//    atmosphere::specific_gaseous_attenuation ()
//    {
//      float gamma;
//
//      gamma = 0.1820*d_frequency*(Noxygen + Nwatervapour);
//    }

    float
    atmosphere::S (size_t index, atmo_element_t element)
    {
      float theta = 300 / d_temperature;
      switch (element)
        {
        case OXYGEN:
          return d_table1[index][1] * 1e-7 * d_oxygen_pressure
              * std::pow (theta, 3)
              * std::exp (d_table1[index][2] * (1 - theta));
          break;
        case WATER_VAPOUR:
          d_table2[index][1] * (1e-1) * d_water_pressure * std::pow (theta, 3.5)
              * std::exp (d_table2[index][2] * (1 - theta));
          break;
        default:
          throw std::runtime_error ("Invalid atmosphere element!");
        }
    }

    float
    atmosphere::F (size_t index, atmo_element_t element)
    {
      float theta = 300 / d_temperature;
      float f0;
      double df;
      double delta = 0;
      double result;

      switch (element)
        {
        case OXYGEN:
          f0 = d_table1[index][0];
          df = d_table1[index][3] * (1e-4)
              * (d_oxygen_pressure * std::pow (theta, 0.8 - d_table1[index][4])
                  + 1.1 * d_water_pressure * theta);
          //TODO: Equation 6b
          delta = (1e-4) * (d_table1[index][5] + d_table1[index][6] * theta)
              * (d_oxygen_pressure + d_water_pressure) * std::pow (theta, 0.8);
          result = (d_frequency / f0)
              * (((df - delta * (f0 - d_frequency))
                  / (std::pow (f0 - d_frequency, 2) + std::pow (df, 2)))
                  + ((df - delta * (f0 + d_frequency))
                      / (std::pow (f0 + d_frequency, 2) + pow (df, 2))));
          break;
        case WATER_VAPOUR:
          f0 = d_table2[index][0];
          df = d_table2[index][3] * 1e-4
              * (d_oxygen_pressure * std::pow (theta, d_table1[index][4])
                  + d_table2[index][5] * d_water_pressure
                      * std::pow (theta, d_table2[index][6]));
          //TODO: Equation 6b
          delta = 0;
          break;
        default:
          throw std::runtime_error ("Invalid atmosphere element!");
        }
      result = (d_frequency / f0)
          * (((df - delta * (f0 - d_frequency))
              / (std::pow (f0 - d_frequency, 2) + std::pow (df, 2)))
              + ((df - delta * (f0 + d_frequency))
                  / (std::pow (f0 + d_frequency, 2) + pow (df, 2))));

      return result;
    }

  } /* namespace leo */
} /* namespace gr */

