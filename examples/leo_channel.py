#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Leo Channel
# Generated: Tue Sep 25 12:15:27 2018
##################################################

from gnuradio import analog
from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from optparse import OptionParser
import leo


class leo_channel(gr.top_block):

    def __init__(self):
        gr.top_block.__init__(self, "Leo Channel")

        ##################################################
        # Variables
        ##################################################
        self.variable_satellite_0 = variable_satellite_0 = leo.satellite_make('ISS', '1 25544U 98067A   18268.52547184  .00016717  00000-0  10270-3 0  9019', '2 25544  51.6373 238.6885 0003885 206.9748 153.1203 15.53729445 14114', 340e6, 500e6, '')
        self.variable_tracker_0 = variable_tracker_0 = leo.tracker_make(variable_satellite_0, 35.3333, 25.1833, 39, '2018-09-25T15:48:25.0000000Z', '2018-09-25T15:58:35.0000000Z', 1e6, '')
        self.variable_test_model_def_0 = variable_test_model_def_0 = leo.test_model_make(variable_tracker_0)
        self.samp_rate = samp_rate = 320e3

        ##################################################
        # Blocks
        ##################################################
        self.leo_channel_model_0 = leo.channel_model(samp_rate, variable_test_model_def_0)
        self.blocks_null_sink_0 = blocks.null_sink(gr.sizeof_gr_complex*1)
        self.analog_sig_source_x_1 = analog.sig_source_c(samp_rate, analog.GR_COS_WAVE, 1000, 1, 0)



        ##################################################
        # Connections
        ##################################################
        self.connect((self.analog_sig_source_x_1, 0), (self.leo_channel_model_0, 0))
        self.connect((self.leo_channel_model_0, 0), (self.blocks_null_sink_0, 0))

    def get_variable_satellite_0(self):
        return self.variable_satellite_0

    def set_variable_satellite_0(self, variable_satellite_0):
        self.variable_satellite_0 = variable_satellite_0

    def get_variable_tracker_0(self):
        return self.variable_tracker_0

    def set_variable_tracker_0(self, variable_tracker_0):
        self.variable_tracker_0 = variable_tracker_0

    def get_variable_test_model_def_0(self):
        return self.variable_test_model_def_0

    def set_variable_test_model_def_0(self, variable_test_model_def_0):
        self.variable_test_model_def_0 = variable_test_model_def_0

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.analog_sig_source_x_1.set_sampling_freq(self.samp_rate)


def main(top_block_cls=leo_channel, options=None):

    tb = top_block_cls()
    tb.start()
    tb.wait()


if __name__ == '__main__':
    main()
