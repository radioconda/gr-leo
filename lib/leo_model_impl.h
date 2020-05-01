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

#ifndef INCLUDED_LEO_LEO_MODEL_IMPL_H
#define INCLUDED_LEO_LEO_MODEL_IMPL_H

#include <leo/leo_model.h>

namespace gr {
namespace leo {
namespace model {
class LEO_API leo_model_impl : public leo_model {

private:
  const impairment_enum_t d_doppler_shift_enum;

  float d_surface_watervap_density;
  float d_temperature;
  float d_rainfall_rate;
  float d_doppler_shift;
  gr_complex d_phase;
  float d_atmo_attenuation;
  float d_rainfall_attenuation;
  float d_pathloss_attenuation;
  float d_pointing_attenuation;
  float d_total_attenuation;
  double d_slant_range;
  double d_elev;
  bool d_write_csv_header;

  generic_attenuation::generic_attenuation_sptr d_atmo_gases_attenuation;
  generic_attenuation::generic_attenuation_sptr d_precipitation_attenuation;
  generic_attenuation::generic_attenuation_sptr d_fspl_attenuation;
  generic_attenuation::generic_attenuation_sptr d_pointing_loss_attenuation;


public:
  leo_model_impl(tracker::tracker_sptr tracker, const uint8_t mode,
                 const uint8_t fspl_attenuation_enum,
                 const uint8_t pointing_attenuation_enum,
                 const uint8_t doppler_shift_enum,
                 const uint8_t atmo_gases_attenuation,
                 const uint8_t precipitation_attenuation,
                 const uint8_t enable_link_margin,
                 const float surface_watervap_density,
                 const float temperature, const float rainfall_rate);

  ~leo_model_impl();

  void
  generic_work(const gr_complex *inbuffer, gr_complex *outbuffer,
               int noutput_items, double samp_rate);

  /*!
   * Calculate the free-space path-loss attenuation for a
   * given slant range.
   * \param slant_range The distance in kilometers between the observer and the
   *      satellite.
   * @return a float representing the attenuation in dB.
   */
  float
  calculate_free_space_path_loss(double slant_range);

  /*!
   * Calculate the Doppler frequency shift for a given satellite range rate.
   * \param velocity The range rate of the satellite expressed in
   * kilometers/sec.
   * @return a float representing the frequency shift in hertz.
   */
  float
  calculate_doppler_shift(double velocity);

  float
  calculate_total_attenuation();

  void
  estimate_link_margin();

  float
  calculate_noise_floor();

  void
  generate_csv_log();

  double
  get_doppler_freq();

};
} // namespace model
} // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_LEO_MODEL_IMPL_H */

