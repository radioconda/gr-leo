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

#ifndef INCLUDED_LEO_GENERIC_MODEL_H
#define INCLUDED_LEO_GENERIC_MODEL_H

#include <leo/api.h>
#include <gnuradio/runtime_types.h>
#include <boost/shared_ptr.hpp>
#include <boost/format.hpp>
#include <leo/tracker.h>

namespace gr
{
  namespace leo
  {

    /*!
     * \brief <+description+>
     *
     */
    class LEO_API generic_model
    {
    public:

      friend class channel_model;

      virtual void
      generic_work (const gr_complex *inbuffer, gr_complex *outbuffer,
                    int noutput_items) = 0;

      static int base_unique_id;

      std::string d_name;
      tracker::tracker_sptr d_tracker;

      int my_id;

      int
      unique_id ();

      std::string
      alias ()
      {
        return (boost::format ("%s%d") % d_name % unique_id ()).str ();
      }

      typedef boost::shared_ptr<generic_model> generic_model_sptr;

      generic_model (void)
      {
      }
      ;

      generic_model (std::string name, tracker::tracker_sptr tracker);

      virtual
      ~generic_model ();

      virtual int
      get_input_item_size ();

      virtual int
      get_output_item_size ();

      virtual tracker::tracker_sptr
      get_tracker ();

    };

  } // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_GENERIC_MODEL_H */

