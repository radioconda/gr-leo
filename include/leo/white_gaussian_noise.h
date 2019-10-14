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

#ifndef INCLUDED_LEO_WHITE_GAUSSIAN_NOISE_H
#define INCLUDED_LEO_WHITE_GAUSSIAN_NOISE_H

#include <leo/api.h>
#include <gnuradio/random.h>
#include <include/leo/generic_noise.h>

namespace gr {
namespace leo {
namespace noise {

class LEO_API white_gaussian_noise : virtual public generic_noise {

public:

  static generic_noise_sptr
  make();

  white_gaussian_noise();

  virtual
  ~white_gaussian_noise();

  void
  add_noise(gr_complex *outbuf, const gr_complex *inbuf, size_t num,
            float snr, float imp);

private:
  gr::random d_rng;

};
} // namespace noise
} // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_WHITE_GAUSSIAN_NOISE_H */

