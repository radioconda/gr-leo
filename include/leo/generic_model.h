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
     * \brief Parent class for LEO_API model objects.
     *
     * \details
     *
     * Parent of a model variable class for LEO_API that will fit
     * into the gr::leo::model block to handle channel simulation.
     *
     * We create objects from LEO_API-derived classes to go into the
     * actual GNU Radio channel model block. Each object contains its own
     * state and so there should be a one-to-one mapping of an LEO_API
     * object and a GR channel model block.
     *
     * This is a pure virtual class and must be derived from by a
     * child class.
     *
     * \sa gr::fec::model::leo_model
     */
    class LEO_API generic_model
    {
    public:

      enum Mode
      {
        UPLINK, DOWNLINK
      };

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

      void
      set_mode (uint8_t mode);

      float
      get_frequency ();

      float
      get_satellite_antenna_gain ();

      float
      get_tracker_antenna_gain ();

      virtual
      ~generic_model ();

      virtual tracker::tracker_sptr
      get_tracker ();

    private:
      uint8_t d_mode;

    };

  } // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_GENERIC_MODEL_H */

