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

#include "channel_model_impl.h"
#include <gnuradio/io_signature.h>
#include <iostream>
#include <string>

namespace gr {
namespace leo {

channel_model::sptr channel_model::make(const double sample_rate,
                                        generic_model::generic_model_sptr model,
                                        const uint8_t noise_type,
                                        const bool store_csv, const char *filename)
{
  return gnuradio::get_initial_sptr(
           new channel_model_impl(sample_rate, model, noise_type, store_csv, filename));
}

/*
 * The private constructor
 */
channel_model_impl::channel_model_impl(const double sample_rate,
                                       generic_model::generic_model_sptr model,
                                       const uint8_t noise_type,
                                       const bool store_csv, const char *filename)
  : gr::sync_block("channel_model",
                   gr::io_signature::make(1, 1, sizeof(gr_complex)),
                   gr::io_signature::make(1, 1, sizeof(gr_complex))),
    d_sample_rate(sample_rate),
    d_time_win_samples(0),
    d_win_produced(0),
    d_model(model),
    d_noise_type(noise_type)


{
  /* A power of 2, should speed up the scheduler */
  set_output_multiple(2048);

  if (!model) {
    std::string msg = name() + ": Invalid model";
    throw std::invalid_argument(msg);
  }

  d_time_win_samples =
    (d_sample_rate * model->get_tracker()->get_time_resolution_us()) / 1e6;

  /* We use Volk underneath for complex multiplication */
  set_alignment(8);

  message_port_register_out(pmt::mp("pdus"));

  switch (d_noise_type) {
  case WHITE_GAUSSIAN:
    d_noise = noise::white_gaussian_noise::make();
    break;
  case NOISE_NONE:
    break;
  default:
    std::string msg = name() + ": Invalid noise type";
    throw std::invalid_argument(msg);
  }

  d_tag.offset = 0;
  d_tag.key = pmt::intern("frequency");
  d_tag.srcid = alias_pmt();
  d_offset = 0;

  if (store_csv == 1) {
    d_fout.open(filename, std::ios::out);
  }

}

/*
 * Our virtual destructor.
 */
channel_model_impl::~channel_model_impl() {}

int channel_model_impl::work(int noutput_items,
                             gr_vector_const_void_star &input_items,
                             gr_vector_void_star &output_items)
{
  const gr_complex *in = (const gr_complex *)input_items[0];
  gr_complex *out = (gr_complex *)output_items[0];

  if (d_model->get_tracker()->is_observation_over()) {
    return WORK_DONE;
  }

  size_t avail = std::min<size_t>(noutput_items,
                                  d_time_win_samples - d_win_produced);
  d_model->generic_work(in, out, avail, d_sample_rate);
  if (d_noise_type != NOISE_NONE) {
    d_noise->add_noise(out, out, avail, d_model->get_noise_floor());
  }

  d_win_produced += avail;

  uint64_t nitems = static_cast<uint64_t>(avail) + nitems_written(0);

  if (d_win_produced == d_time_win_samples) {
    d_win_produced = 0;
    d_model->advance_time(d_model->get_tracker()->get_time_resolution_us());
    /* Produce messages only in case we have AOS */
    if (d_model->aos()) {
      d_tag.offset = nitems + d_time_win_samples;

      d_tags_vec = d_model->get_tags_vector();
      std::vector<std::pair<pmt::pmt_t, pmt::pmt_t>>::iterator it;

      pmt::pmt_t dict = pmt::make_dict();
      for (it = d_tags_vec.begin(); it != d_tags_vec.end(); it++) {
        d_tag.key = (*it).first;
        d_tag.value = (*it).second;
        add_item_tag(0, d_tag);

        dict = pmt::dict_add(dict, (*it).first, (*it).second);
      }

      const std::string &str = d_model->get_csv_log();
      d_fout << str.c_str() << "\n";
      pmt::pmt_t t = pmt::init_c32vector(d_time_win_samples, out);
//      gr_complex* tmp = c32vector_writable_elements(t, d_time_win_samples);
//      memcpy(tmp, out, d_time_win_samples*sizeof(gr_complex));
      message_port_pub(pmt::mp("pdus"),
                       pmt::cons(dict,
                                 t));
    }
  }

  return avail;
}

} /* namespace leo */
} /* namespace gr */
