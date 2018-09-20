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

#include <leo/generic_model.h>
#include <iostream>

namespace gr
{
  namespace leo
  {

    generic_model::generic_model (std::string name) :
            d_name (name)
    {
      my_id = base_unique_id++;
    }

    generic_model::~generic_model ()
    {
    }

    int
    generic_model::get_input_item_size ()
    {
      return sizeof(gr_complex);
    }

    int
    generic_model::get_output_item_size ()
    {
      return sizeof(gr_complex);
    }

    int generic_model::base_unique_id = 1;

    int
    generic_model::unique_id ()
    {
      return my_id;
    }

  } /* namespace leo */
} /* namespace gr */
