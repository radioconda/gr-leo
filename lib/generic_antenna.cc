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
#include <leo/utils/helper.h>
#include <leo/generic_antenna.h>

namespace gr {
namespace leo {

generic_antenna::generic_antenna(uint8_t type, double frequency,
                                 int polarization, double pointing_error) :
  d_type(type),
  d_frequency(frequency),
  d_polarization(polarization),
  d_pointing_error(utils::degrees_to_radians(pointing_error))
{
  my_id = base_unique_id++;
}

generic_antenna::~generic_antenna()
{
}

double
generic_antenna::get_frequency()
{
  return d_frequency;
}

double
generic_antenna::get_pointing_error()
{
  return d_pointing_error;
}

void
generic_antenna::set_pointing_error(double error)
{
  d_pointing_error = utils::degrees_to_radians(error);
}

double
generic_antenna::get_wavelength()
{
  return LIGHT_SPEED / d_frequency;
}

int
generic_antenna::get_polarization()
{
  // FIXME
  return d_polarization;
}

int generic_antenna::base_unique_id = 1;

int
generic_antenna::unique_id()
{
  return my_id;
}

} /* namespace leo */
} /* namespace gr */

