/*
 * Copyright 2011 Free Software Foundation, Inc.
 *
 * This file is a part of gr-leo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef INCLUDED_LEO_TYPES_H
#define INCLUDED_LEO_TYPES_H

#include <gnuradio/leo/api.h>
#include <string>

namespace gr {
namespace leo {

/*!
 * A struct that contains information about the acquisition of signal (AOS),
 * the loss of signal (LOS) and max elevation of a satellite pass.
 */
typedef struct {
  std::string aos;
  std::string los;
  double max_elevation;
} pass_details_t;

enum impairment_enum_t {
  IMPAIRMENT_NONE = 0,
  ATMO_GASES_ITU,
  ATMO_GASES_REGRESSION,
  PRECIPITATION_ITU,
  PRECIPITATION_CUSTOM,
  FREE_SPACE_PATH_LOSS,
  ANTENNA_POINTING_LOSS,
  DOPPLER_SHIFT
};

enum noise_t {
  NOISE_NONE = 0,
  WHITE_GAUSSIAN
};

enum polarization_t {
  RHCP = 0, LHCP, LINEAR_VERTICAL, LINEAR_HORIZONTAL
};

enum antenna_t {
  YAGI,
  HELIX,
  PARABOLIC_REFLECTOR,
  CANTED_TURNSTYLE,
  CUSTOM,
  MONOPOLE,
  DIPOLE,
  QUADRIFILAR_HELIX
};

enum link_mode_t {
  UPLINK,
  DOWNLINK
};


} // namespace leo
} // namespace gr

#endif
