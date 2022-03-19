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

#ifndef INCLUDED_LEO_FREE_SPACE_PATH_LOSS_IMPL_H
#define INCLUDED_LEO_FREE_SPACE_PATH_LOSS_IMPL_H

#include "../include/gnuradio/leo/free_space_path_loss.h"
#include <vector>

namespace gr {
namespace leo {
namespace attenuation {
/*
 * Calculate Free-Space path-loss based on ITU R-REC-P.619
 */
class LEO_API free_space_path_loss_impl : public free_space_path_loss {

public:
  free_space_path_loss_impl();

  ~free_space_path_loss_impl();

  double
  get_attenuation();

};
} // namespace attenuation
} // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_FREE_SPACE_PATH_LOSS_IMPL_H */

