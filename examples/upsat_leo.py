#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: UPSAT channel simulation
# Author: Kostis Triantafyllakis (kostastriantaf@gmail.com)
# Description: An example of LEO channel simulation using the UPSAT transmitter from gr-satnogs.
# GNU Radio version: 3.7.13.5
##################################################

from distutils.version import StrictVersion

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print "Warning: failed to XInitThreads()"

from PyQt5 import Qt
from PyQt5 import Qt, QtCore
from gnuradio import analog
from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import filter
from gnuradio import gr
from gnuradio import qtgui
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from optparse import OptionParser
import leo
import math
import numpy
import pmt
import satnogs
import sip
import sys
from gnuradio import qtgui


class upsat_leo(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "UPSAT channel simulation")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("UPSAT channel simulation")
        qtgui.util.check_set_qss()
        try:
            self.setWindowIcon(Qt.QIcon.fromTheme('gnuradio-grc'))
        except:
            pass
        self.top_scroll_layout = Qt.QVBoxLayout()
        self.setLayout(self.top_scroll_layout)
        self.top_scroll = Qt.QScrollArea()
        self.top_scroll.setFrameStyle(Qt.QFrame.NoFrame)
        self.top_scroll_layout.addWidget(self.top_scroll)
        self.top_scroll.setWidgetResizable(True)
        self.top_widget = Qt.QWidget()
        self.top_scroll.setWidget(self.top_widget)
        self.top_layout = Qt.QVBoxLayout(self.top_widget)
        self.top_grid_layout = Qt.QGridLayout()
        self.top_layout.addLayout(self.top_grid_layout)

        self.settings = Qt.QSettings("GNU Radio", "upsat_leo")
        self.restoreGeometry(self.settings.value("geometry", type=QtCore.QByteArray))


        ##################################################
        # Variables
        ##################################################


        self.satellite_tx_antenna = satellite_tx_antenna = leo.dipole_antenna_make(5, 435.769e6, 3, 0)



        self.satellite_rx_antenna = satellite_rx_antenna = leo.dipole_antenna_make(5, 435.765e6, 3, 0)

        self.variable_satellite_0 = variable_satellite_0 = leo.satellite_make('UPSAT', '1 25544U 98067A   18268.52547184  .00016717  00000-0  10270-3 0  9019', '2 25544  51.6373 238.6885 0003885 206.9748 153.1203 15.53729445 14114', 435e6, 435e6, satellite_tx_antenna, satellite_rx_antenna)


        self.tracker_tx_antenna = tracker_tx_antenna = leo.yagi_antenna_make(0, 435.765e6, 0, 0, 2.35)



        self.tracker_rx_antenna = tracker_rx_antenna = leo.yagi_antenna_make(0, 435.769e6, 2, 0, 0)

        self.samples_per_symbol_tx = samples_per_symbol_tx = 40
        self.variable_tracker_0 = variable_tracker_0 = leo.tracker_make(variable_satellite_0, 35.3333, 25.1833, 1, '2018-09-25T15:48:25.0000000Z', '2018-09-25T15:58:35.0000000Z', 1000, 435E6,
                    435e6,
                    tracker_tx_antenna,
                    tracker_rx_antenna)
        self.sq_wave = sq_wave = (1.0, ) * samples_per_symbol_tx
        self.gaussian_taps = gaussian_taps = filter.firdes.gaussian(1.0, samples_per_symbol_tx, 1.0, 4*samples_per_symbol_tx)
        self.variable_leo_model_def_0 = variable_leo_model_def_0 = leo.leo_model_make(variable_tracker_0, 1, 5,
          													0, 7,
          													2, 4,
          													7.5, 20, 90)
        self.tx_frequency = tx_frequency = 145.835e6
        self.space_freq = space_freq = 1200.0
        self.samp_rate_tx = samp_rate_tx = 48e3
        self.mark_freq = mark_freq = 2200.0
        self.interp_taps = interp_taps = numpy.convolve(numpy.array(gaussian_taps), numpy.array(sq_wave))
        self.baud_rate = baud_rate = 1200

        ##################################################
        # Blocks
        ##################################################
        self.satnogs_upsat_fsk_frame_encoder_0 = satnogs.upsat_fsk_frame_encoder([0x33]*8, [0x7A, 0x0E], False, True, False, True, True, 'ABCD', 0, 'UPSAT', 0, 512)
        self.satnogs_multi_format_msg_sink_0 = satnogs.multi_format_msg_sink(0, False, True, '/home/ctriant/test.txt')
        self.qtgui_waterfall_sink_x_0 = qtgui.waterfall_sink_c(
        	4096, #size
        	firdes.WIN_BLACKMAN_hARRIS, #wintype
        	0, #fc
        	samp_rate_tx, #bw
        	"UPSAT", #name
                1 #number of inputs
        )
        self.qtgui_waterfall_sink_x_0.set_update_time(0.10)
        self.qtgui_waterfall_sink_x_0.enable_grid(False)
        self.qtgui_waterfall_sink_x_0.enable_axis_labels(True)

        if not False:
          self.qtgui_waterfall_sink_x_0.disable_legend()

        if "complex" == "float" or "complex" == "msg_float":
          self.qtgui_waterfall_sink_x_0.set_plot_pos_half(not True)

        labels = ['', '', '', '', '',
                  '', '', '', '', '']
        colors = [0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
                  1.0, 1.0, 1.0, 1.0, 1.0]
        for i in xrange(1):
            if len(labels[i]) == 0:
                self.qtgui_waterfall_sink_x_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_waterfall_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_waterfall_sink_x_0.set_color_map(i, colors[i])
            self.qtgui_waterfall_sink_x_0.set_line_alpha(i, alphas[i])

        self.qtgui_waterfall_sink_x_0.set_intensity_range(-140, 10)

        self._qtgui_waterfall_sink_x_0_win = sip.wrapinstance(self.qtgui_waterfall_sink_x_0.pyqwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_waterfall_sink_x_0_win, 0, 0, 3, 2)
        for r in range(0, 3):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(0, 2):
            self.top_grid_layout.setColumnStretch(c, 1)
        self.qtgui_time_sink_x_0 = qtgui.time_sink_c(
        	1024, #size
        	samp_rate_tx, #samp_rate
        	"", #name
        	1 #number of inputs
        )
        self.qtgui_time_sink_x_0.set_update_time(0.10)
        self.qtgui_time_sink_x_0.set_y_axis(-1, 1)

        self.qtgui_time_sink_x_0.set_y_label('Amplitude', "")

        self.qtgui_time_sink_x_0.enable_tags(-1, True)
        self.qtgui_time_sink_x_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, 0, "")
        self.qtgui_time_sink_x_0.enable_autoscale(True)
        self.qtgui_time_sink_x_0.enable_grid(False)
        self.qtgui_time_sink_x_0.enable_axis_labels(True)
        self.qtgui_time_sink_x_0.enable_control_panel(False)
        self.qtgui_time_sink_x_0.enable_stem_plot(False)

        if not False:
          self.qtgui_time_sink_x_0.disable_legend()

        labels = ['', '', '', '', '',
                  '', '', '', '', '']
        widths = [1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        colors = ["blue", "red", "green", "black", "cyan",
                  "magenta", "yellow", "dark red", "dark green", "blue"]
        styles = [1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        markers = [-1, -1, -1, -1, -1,
                   -1, -1, -1, -1, -1]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
                  1.0, 1.0, 1.0, 1.0, 1.0]

        for i in xrange(2):
            if len(labels[i]) == 0:
                if(i % 2 == 0):
                    self.qtgui_time_sink_x_0.set_line_label(i, "Re{{Data {0}}}".format(i/2))
                else:
                    self.qtgui_time_sink_x_0.set_line_label(i, "Im{{Data {0}}}".format(i/2))
            else:
                self.qtgui_time_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_time_sink_x_0.set_line_width(i, widths[i])
            self.qtgui_time_sink_x_0.set_line_color(i, colors[i])
            self.qtgui_time_sink_x_0.set_line_style(i, styles[i])
            self.qtgui_time_sink_x_0.set_line_marker(i, markers[i])
            self.qtgui_time_sink_x_0.set_line_alpha(i, alphas[i])

        self._qtgui_time_sink_x_0_win = sip.wrapinstance(self.qtgui_time_sink_x_0.pyqwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_time_sink_x_0_win, 3, 1, 1, 1)
        for r in range(3, 4):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(1, 2):
            self.top_grid_layout.setColumnStretch(c, 1)
        self.qtgui_freq_sink_x_0 = qtgui.freq_sink_c(
        	4096, #size
        	firdes.WIN_BLACKMAN_hARRIS, #wintype
        	0, #fc
        	samp_rate_tx, #bw
        	"", #name
        	1 #number of inputs
        )
        self.qtgui_freq_sink_x_0.set_update_time(0.10)
        self.qtgui_freq_sink_x_0.set_y_axis(-140, 10)
        self.qtgui_freq_sink_x_0.set_y_label('Relative Gain', 'dB')
        self.qtgui_freq_sink_x_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, 0.0, 0, "")
        self.qtgui_freq_sink_x_0.enable_autoscale(False)
        self.qtgui_freq_sink_x_0.enable_grid(False)
        self.qtgui_freq_sink_x_0.set_fft_average(1.0)
        self.qtgui_freq_sink_x_0.enable_axis_labels(True)
        self.qtgui_freq_sink_x_0.enable_control_panel(False)

        if not False:
          self.qtgui_freq_sink_x_0.disable_legend()

        if "complex" == "float" or "complex" == "msg_float":
          self.qtgui_freq_sink_x_0.set_plot_pos_half(not True)

        labels = ['', '', '', '', '',
                  '', '', '', '', '']
        widths = [1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        colors = ["blue", "red", "green", "black", "cyan",
                  "magenta", "yellow", "dark red", "dark green", "dark blue"]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
                  1.0, 1.0, 1.0, 1.0, 1.0]
        for i in xrange(1):
            if len(labels[i]) == 0:
                self.qtgui_freq_sink_x_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_freq_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_freq_sink_x_0.set_line_width(i, widths[i])
            self.qtgui_freq_sink_x_0.set_line_color(i, colors[i])
            self.qtgui_freq_sink_x_0.set_line_alpha(i, alphas[i])

        self._qtgui_freq_sink_x_0_win = sip.wrapinstance(self.qtgui_freq_sink_x_0.pyqwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_freq_sink_x_0_win, 3, 0, 1, 1)
        for r in range(3, 4):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(0, 1):
            self.top_grid_layout.setColumnStretch(c, 1)
        self.leo_channel_model_0 = leo.channel_model(samp_rate_tx, variable_leo_model_def_0, 1, -100, 1)
        self.interp_fir_filter_xxx_0 = filter.interp_fir_filter_fff(samples_per_symbol_tx, (interp_taps))
        self.interp_fir_filter_xxx_0.declare_sample_delay(0)
        self.blocks_multiply_const_vxx_0 = blocks.multiply_const_vcc((1e5, ))
        self.blocks_message_strobe_0 = blocks.message_strobe(pmt.intern("TEST"), 1000)
        self.blocks_float_to_complex_0 = blocks.float_to_complex(1)
        self.blocks_add_xx_0 = blocks.add_vcc(1)
        self.analog_noise_source_x_0 = analog.noise_source_c(analog.GR_GAUSSIAN, 0.0001, 0)



        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.blocks_message_strobe_0, 'strobe'), (self.satnogs_upsat_fsk_frame_encoder_0, 'pdu'))
        self.msg_connect((self.leo_channel_model_0, 'csv'), (self.satnogs_multi_format_msg_sink_0, 'in'))
        self.connect((self.analog_noise_source_x_0, 0), (self.blocks_add_xx_0, 1))
        self.connect((self.blocks_add_xx_0, 0), (self.qtgui_freq_sink_x_0, 0))
        self.connect((self.blocks_add_xx_0, 0), (self.qtgui_time_sink_x_0, 0))
        self.connect((self.blocks_add_xx_0, 0), (self.qtgui_waterfall_sink_x_0, 0))
        self.connect((self.blocks_float_to_complex_0, 0), (self.blocks_multiply_const_vxx_0, 0))
        self.connect((self.blocks_multiply_const_vxx_0, 0), (self.leo_channel_model_0, 0))
        self.connect((self.interp_fir_filter_xxx_0, 0), (self.blocks_float_to_complex_0, 0))
        self.connect((self.leo_channel_model_0, 0), (self.blocks_add_xx_0, 0))
        self.connect((self.satnogs_upsat_fsk_frame_encoder_0, 0), (self.interp_fir_filter_xxx_0, 0))

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "upsat_leo")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()

    def get_satellite_tx_antenna(self):
        return self.satellite_tx_antenna

    def set_satellite_tx_antenna(self, satellite_tx_antenna):
        self.satellite_tx_antenna = satellite_tx_antenna
        self.satellite_tx_antenna.set_pointing_error(0)

    def get_satellite_rx_antenna(self):
        return self.satellite_rx_antenna

    def set_satellite_rx_antenna(self, satellite_rx_antenna):
        self.satellite_rx_antenna = satellite_rx_antenna
        self.satellite_rx_antenna.set_pointing_error(0)

    def get_variable_satellite_0(self):
        return self.variable_satellite_0

    def set_variable_satellite_0(self, variable_satellite_0):
        self.variable_satellite_0 = variable_satellite_0

    def get_tracker_tx_antenna(self):
        return self.tracker_tx_antenna

    def set_tracker_tx_antenna(self, tracker_tx_antenna):
        self.tracker_tx_antenna = tracker_tx_antenna
        self.tracker_tx_antenna.set_pointing_error(0)

    def get_tracker_rx_antenna(self):
        return self.tracker_rx_antenna

    def set_tracker_rx_antenna(self, tracker_rx_antenna):
        self.tracker_rx_antenna = tracker_rx_antenna
        self.tracker_rx_antenna.set_pointing_error(0)

    def get_samples_per_symbol_tx(self):
        return self.samples_per_symbol_tx

    def set_samples_per_symbol_tx(self, samples_per_symbol_tx):
        self.samples_per_symbol_tx = samples_per_symbol_tx
        self.set_sq_wave((1.0, ) * self.samples_per_symbol_tx)
        self.set_gaussian_taps(filter.firdes.gaussian(1.0, self.samples_per_symbol_tx, 1.0, 4*self.samples_per_symbol_tx))

    def get_variable_tracker_0(self):
        return self.variable_tracker_0

    def set_variable_tracker_0(self, variable_tracker_0):
        self.variable_tracker_0 = variable_tracker_0

    def get_sq_wave(self):
        return self.sq_wave

    def set_sq_wave(self, sq_wave):
        self.sq_wave = sq_wave
        self.set_interp_taps(numpy.convolve(numpy.array(self.gaussian_taps), numpy.array(self.sq_wave)))

    def get_gaussian_taps(self):
        return self.gaussian_taps

    def set_gaussian_taps(self, gaussian_taps):
        self.gaussian_taps = gaussian_taps
        self.set_interp_taps(numpy.convolve(numpy.array(self.gaussian_taps), numpy.array(self.sq_wave)))

    def get_variable_leo_model_def_0(self):
        return self.variable_leo_model_def_0

    def set_variable_leo_model_def_0(self, variable_leo_model_def_0):
        self.variable_leo_model_def_0 = variable_leo_model_def_0

    def get_tx_frequency(self):
        return self.tx_frequency

    def set_tx_frequency(self, tx_frequency):
        self.tx_frequency = tx_frequency

    def get_space_freq(self):
        return self.space_freq

    def set_space_freq(self, space_freq):
        self.space_freq = space_freq

    def get_samp_rate_tx(self):
        return self.samp_rate_tx

    def set_samp_rate_tx(self, samp_rate_tx):
        self.samp_rate_tx = samp_rate_tx
        self.qtgui_waterfall_sink_x_0.set_frequency_range(0, self.samp_rate_tx)
        self.qtgui_time_sink_x_0.set_samp_rate(self.samp_rate_tx)
        self.qtgui_freq_sink_x_0.set_frequency_range(0, self.samp_rate_tx)

    def get_mark_freq(self):
        return self.mark_freq

    def set_mark_freq(self, mark_freq):
        self.mark_freq = mark_freq

    def get_interp_taps(self):
        return self.interp_taps

    def set_interp_taps(self, interp_taps):
        self.interp_taps = interp_taps
        self.interp_fir_filter_xxx_0.set_taps((self.interp_taps))

    def get_baud_rate(self):
        return self.baud_rate

    def set_baud_rate(self, baud_rate):
        self.baud_rate = baud_rate


def main(top_block_cls=upsat_leo, options=None):

    qapp = Qt.QApplication(sys.argv)

    tb = top_block_cls()
    tb.start()
    tb.show()

    def quitting():
        tb.stop()
        tb.wait()
    qapp.aboutToQuit.connect(quitting)
    qapp.exec_()


if __name__ == '__main__':
    main()
