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
#include <gnuradio/leo/generic_attenuation.h>

namespace gr {
namespace leo {

double generic_attenuation::frequency = 0;
double generic_attenuation::elevation_angle = 0;
double generic_attenuation::slant_range = 0;
polarization_t generic_attenuation::polarization = RHCP;

generic_attenuation::generic_attenuation_sptr
generic_attenuation::make()
{
  return generic_attenuation::generic_attenuation_sptr();
}

generic_attenuation::generic_attenuation()
{
}

generic_attenuation::~generic_attenuation()
{
}

void
generic_attenuation::set_frequency(double freq)
{
  frequency = freq / 1e9;
}

void
generic_attenuation::set_slant_range(double range)
{
  slant_range = range;
}

void
generic_attenuation::set_polarization(polarization_t polar)
{
  polarization = polar;
}

void
generic_attenuation::set_elevation_angle(double elev_angle)
{
  elevation_angle = elev_angle;
}

} /* namespace leo */
} /* namespace gr */

