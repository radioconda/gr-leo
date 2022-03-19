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

#include "free_space_path_loss_impl.h"
#include <cmath>
#include <gnuradio/leo/log.h>

namespace gr {
namespace leo {
namespace attenuation {

generic_attenuation::generic_attenuation_sptr
free_space_path_loss::make()
{
  return generic_attenuation::generic_attenuation_sptr(
           new free_space_path_loss_impl());
}

free_space_path_loss_impl::free_space_path_loss_impl() :
  generic_attenuation()
{
}

free_space_path_loss_impl::~free_space_path_loss_impl()
{
}

double
free_space_path_loss_impl::get_attenuation()
{
  double attenuation = 0;
  double path_loss = 0;

  return 92.45 + 20 * std::log10(slant_range * frequency);
}

} /* namespace attenuation */
} /* namespace leo */
} /* namespace gr */

