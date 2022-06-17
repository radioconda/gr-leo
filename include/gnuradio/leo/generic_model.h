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

#ifndef INCLUDED_LEO_GENERIC_MODEL_H
#define INCLUDED_LEO_GENERIC_MODEL_H

#include <gnuradio/leo/api.h>
#include <gnuradio/leo/leo_types.h>
#include <gnuradio/leo/tracker.h>
#include <gnuradio/leo/generic_attenuation.h>
#include <gnuradio/leo/link_margin.h>
#include <gnuradio/runtime_types.h>
#include <boost/format.hpp>
#include <memory>

namespace gr {
namespace leo {

/*!
 * \brief Parent class for model objects.
 *
 * \details
 *
 * Parent of a channel impairment model class that will fit as a
 * parameter into the gr::leo::channel_model block.
 *
 * We create objects from derived classes to go into the
 * actual GNU Radio channel_model block. Each object describes a different
 * telecommunication channel and must implement the pure virtual function generic_work,
 * in which the input signal is attenuated and transformed appropriately.
 *
 * A derived model class may declare various gr::leo::generic_attenuation objects
 * that can be used inside the generic_work, in order to estimate different type of losses.
 *
 * \sa gr::fec::model::leo_model
 */
class LEO_API generic_model {
public:

  /*!
   * \brief Pure virtual function that must be implemented by every
   * derived class and is responsible to apply all the appropriate
   * transformations and apply the available types of attenuation to the
   * input signal, as they are described by the corresponding channel model.
   *
   * \param inbuffer Pointer to the complex input signal
   * \param outbuffer Pointer to the complex input signal
   * \param noutput_items The number of available input samples to process
   *
   * process
   */
  virtual void
  generic_work(const gr_complex *inbuffer, gr_complex *outbuffer,
               int noutput_items, double samp_rate) = 0;

  /**
   * Advances the time of the simulation
   * @param us the time window to advance, expressed in microseconds
   */
  virtual void
  advance_time(double us);

  static int base_unique_id;

  std::string d_name;

  int my_id;

  int
  unique_id();

  std::string
  alias()
  {
    return (boost::format("%s%d") % d_name % unique_id()).str();
  }

  using generic_model_sptr = std::shared_ptr<generic_model>;

  /*!
   * \brief The constructor of generic_model class
   *
   * \param name The name of the channel model
   * \param tracker A boost::shared_ptr to the constructed tracker object
   * \param mode The transmission mode
   *
   * \return a boost::shared_ptr to the constructed tracker object
   */
  generic_model(std::string name, tracker::tracker_sptr tracker,
                const link_mode_t mode);

  generic_model(void) {};

  /*!
   * \brief Get the tracker object
   * \return a boost::shared_ptr to the constructed tracker object
   */
  tracker::tracker_sptr
  get_tracker();

  /*!
   * \brief Get the correct operating frequency based on the transmission mode
   * \return the frequency in Hz
   */
  double
  get_frequency();

  /*!
   * \brief Get the correct polarization based on the transmission mode
   * \return the polarization enumeration
   */
  polarization_t
  get_polarization();

  /*!
   * \brief Get the appropriate satellite antenna gain for the cases of uplink and
   * downlink mode.
   * \return the satellite antenna gain in dBiC.
   */
  double
  get_satellite_antenna_gain();

  /*!
   * \brief Get the appropriate TX power for the cases of uplink and
   * downlink mode.
   * \return the TX power in dBm.
   */
  double
  get_tx_power_dbm();

  double
  get_receiver_bandwidth();

  double
  get_noise_temperature();

  double
  get_noise_figure();

  /*!
   * \brief Get the appropriate satellite antenna for the cases of uplink and
   * downlink mode.
   * \return a boost::shared_ptr to the satellite antenna.
   */
  generic_antenna::generic_antenna_sptr
  get_tracker_antenna();

  /*!
   * \brief Get the appropriate tracker antenna gain for the cases of uplink and
   * downlink mode.
   * \return the tracker antenna gain in dBiC.
   */
  double
  get_tracker_antenna_gain();

  /*!
   * \brief Get the appropriate tracker antenna for the cases of uplink and
   * downlink mode.
   * \return a boost::shared_ptr to the tracker antenna.
   */
  generic_antenna::generic_antenna_sptr
  get_satellite_antenna();

  /*!
   * \brief This functions retrieves periodically orbit information from the tracker
   * and updates the corresponding static variables of the generic_attenuation class.
   */
  void
  orbit_update();

  /*!
   * \brief Get the model's log as a CSV formatted string.
   * \return the string log
   */
  virtual std::string
  get_csv_log() = 0;

  /*!
   * \brief Get the model's noise-floor.
   * \return the noise-floor in dBm
   */
  double
  get_noise_floor();

  bool
  aos();

  virtual void
  estimate_link_margin() = 0;

  virtual double
  calculate_noise_floor() = 0;

  /*!
   * \brief Get the resulting frequency with the effect of Doppler.
   * If the Doppler is not enabled, this will be the uplink or downlink
   * frequency.
   * \return the freuency with the effect of Doppler
   */
  virtual double
  get_doppler_freq() = 0;

  virtual
  ~generic_model();

protected:
  /*!
   * \brief Represents the uplink or downlink transmission mode
   */
  link_mode_t d_mode;
  tracker::tracker_sptr d_tracker;
  double d_noise_floor;

  /*!
   * \brief A shared pointer to the link margin class
   */
  link_margin::link_margin_sptr d_link_margin;

  double d_link_margin_db;

};

} // namespace leo
} // namespace gr

#endif /* INCLUDED_LEO_GENERIC_MODEL_H */

