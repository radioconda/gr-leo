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

#ifndef INCLUDED_LEO_CHANNEL_MODEL_IMPL_H
#define INCLUDED_LEO_CHANNEL_MODEL_IMPL_H

#include <leo/channel_model.h>
#include <leo/generic_noise.h>
#include <leo/white_gaussian_noise.h>


namespace gr
{
  namespace leo
  {

    class channel_model_impl : public channel_model
    {
    private:
      /*!
       * \brief The sampling rate
       */
      const float d_sample_rate;

      /*!
       * \brief The interval between every orbit calculation that is
       * done by tracker in microseconds.
       */
      float d_time_resolution_us;

      /*!
       * \brief The interval between every orbit calculation that is
       * done by tracker in samples.
       */
      size_t d_time_resolution_samples;

      /*!
       * \brief A shared pointer to the variable model
       */
      generic_model::generic_model_sptr d_model;


      uint8_t d_noise_type;


      float d_snr;

      generic_noise::generic_noise_sptr d_noise;

    public:
      channel_model_impl (const float sample_rate,
                          generic_model::generic_model_sptr model, const uint8_t noise_type, float snr=0);

      ~channel_model_impl ();

      int
      work (int noutput_items, gr_vector_const_void_star &input_items,
            gr_vector_void_star &output_items);
    };

  } // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_CHANNEL_MODEL_IMPL_H */

