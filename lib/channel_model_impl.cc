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
#include "channel_model_impl.h"
#include <iostream>
#include <string>

namespace gr {
namespace leo {

channel_model::sptr
channel_model::make(const float sample_rate,
                    generic_model::generic_model_sptr model,
                    const uint8_t noise_type)
{
  return gnuradio::get_initial_sptr(
           new channel_model_impl(sample_rate, model, noise_type));
}

/*
 * The private constructor
 */
channel_model_impl::channel_model_impl(
  const float sample_rate, generic_model::generic_model_sptr model,
  const uint8_t noise_type) :
  gr::sync_block("channel_model",
                 gr::io_signature::make(1, 1, sizeof(gr_complex)),
                 gr::io_signature::make(1, 1, sizeof(gr_complex))),
  d_sample_rate(sample_rate),
  d_time_win_samples(0),
  d_win_produced(0),
  d_model(model),
  d_noise_type(noise_type)
{
  if (!model) {
    std::string msg = name() +  ": Invalid model";
    throw std::invalid_argument(msg);
  }

  d_time_win_samples = (d_sample_rate *
                        model->get_tracker()->get_time_resolution_us()) / 1e6;

  /* A power of 2, should speed up the scheduler */
  set_output_multiple(2048);

  /* We use Volk underneath for complex multiplication */
  set_alignment(8);

  message_port_register_out(pmt::mp("csv"));
  message_port_register_out(pmt::mp("doppler"));

  switch (d_noise_type) {
  case WHITE_GAUSSIAN:
    d_noise = noise::white_gaussian_noise::make();
    break;
  case NOISE_NONE:
    break;
  default:
    std::string msg = name() +  ": Invalid noise type";
    throw std::invalid_argument(msg);
  }
}

/*
 * Our virtual destructor.
 */
channel_model_impl::~channel_model_impl()
{
}

int
channel_model_impl::work(int noutput_items,
                         gr_vector_const_void_star &input_items,
                         gr_vector_void_star &output_items)
{
  const gr_complex *in = (const gr_complex *) input_items[0];
  gr_complex *out = (gr_complex *) output_items[0];

  if (d_model->get_tracker()->is_observation_over()) {
    return WORK_DONE;
  }

  size_t avail = std::min<size_t>(noutput_items,
                                  d_time_win_samples - d_win_produced);
  d_model->generic_work(in, out, avail, d_sample_rate);
  if (d_noise_type != NOISE_NONE) {
    d_noise->add_noise(out, out, avail, d_model->get_noise_floor());
  }

  /* Produce messages only in case we have AOS */
  if (d_model->aos()) {
    const std::string &str = d_model->get_csv_log();
    message_port_pub(pmt::mp("csv"),
                     pmt::make_blob(str.c_str(), str.length()));
    message_port_pub(pmt::mp("doppler"),
                     pmt::from_double(d_model->get_doppler_freq()));
  }
  d_win_produced += avail;

  if (d_win_produced == d_time_win_samples) {
    d_win_produced = 0;
    d_model->advance_time(d_model->get_tracker()->get_time_resolution_us());
  }

  return noutput_items;
}

} /* namespace leo */
} /* namespace gr */

