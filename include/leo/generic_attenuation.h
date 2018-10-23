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

#ifndef INCLUDED_LEO_GENERIC_ATTENUATION_H
#define INCLUDED_LEO_GENERIC_ATTENUATION_H

#include <leo/api.h>
#include <string>
#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>

namespace gr
{
  namespace leo
  {

    /*!
     * \brief Parent class for LEO_API attenuation objects.
     *
     */
    class LEO_API generic_attenuation
    {

    public:

      /*!
       * \brief Get the estimated attenuation. This pure virtual
       * function MUST be implemented by every derived class.
       * \return the attenuation in dB.
       */
      virtual float
      get_attenuation (float elevation) = 0;

      typedef boost::shared_ptr<generic_attenuation> generic_attenuation_sptr;

      static generic_attenuation::generic_attenuation_sptr
      make ();

      virtual
      ~generic_attenuation ();

      generic_attenuation ();

    };
  } // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_GENERIC_ATTENUATION_H */

