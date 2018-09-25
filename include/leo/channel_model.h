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

#ifndef INCLUDED_LEO_CHANNEL_MODEL_H
#define INCLUDED_LEO_CHANNEL_MODEL_H

#include <leo/api.h>
#include <leo/generic_model.h>
#include <gnuradio/sync_block.h>
#include <string>

namespace gr
{
  namespace leo
  {

    /*!
     * \brief <+description of block+>
     * \ingroup leo
     *
     */
    class LEO_API channel_model : virtual public gr::sync_block
    {
    public:
      typedef boost::shared_ptr<channel_model> sptr;
      /*!
       * \brief Return a shared_ptr to a new instance of leo::channel_model.
       *
       * To avoid accidental use of raw pointers, leo::channel_model's
       * constructor is in a private implementation
       * class. leo::channel_model::make is the public interface for
       * creating new instances.
       */
      static sptr
      make (const float sample_rate, generic_model::generic_model_sptr);
    };

  } // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_CHANNEL_MODEL_H */

