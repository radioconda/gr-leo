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

#ifndef INCLUDED_LEO_LEO_MODEL_IMPL_H
#define INCLUDED_LEO_LEO_MODEL_IMPL_H

#include "../include/leo/leo_model.h"
#include <gnuradio/fxpt_nco.h>

namespace gr
{
  namespace leo
  {
    namespace model
    {
      class LEO_API leo_model_impl : public leo_model
      {

      private:
        gr::fxpt_nco d_nco;
        atmosphere* d_atmosphere;

      public:
        leo_model_impl ();

        ~leo_model_impl ();

        void
        generic_work (const gr_complex *inbuffer, gr_complex *outbuffer,
                      int noutput_items);

        /*!
         * Calculate the free-space path-loss attenuation for a
         * given slant range.
         * \param slant_range The distance in kilometers between the observer and the
         *      satellite.
         * @return a float representing the attenuation in dB.
         */
        float
        calculate_free_space_path_loss (double slant_range);

        /*!
         * Calculate the Doppler frequency shift for a given satellite range rate.
         * \param velocity The range rate of the satellite expressed in
         * kilometers/sec.
         * @return a float representing the frequency shift in hertz.
         */
        float
        calculate_doppler_shift (double velocity);

      };
    } // namespace model
  } // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_LEO_MODEL_IMPL_H */

