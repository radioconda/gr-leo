#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# SPDX-License-Identifier: GPL-3.0
#
# GNU Radio Python Flow Graph
# Title: LEO channel simulation
# Author: Kostis Triantafyllakis (kostastriantaf@gmail.com)
# GNU Radio version: 3.8.0.0

from distutils.version import StrictVersion

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print("Warning: failed to XInitThreads()")

from PyQt5 import Qt
from gnuradio import qtgui
from gnuradio.filter import firdes
import sip
from gnuradio import analog
from gnuradio import gr
import sys
import signal
from argparse import ArgumentParser
from gnuradio.eng_arg import eng_float, intx
from gnuradio import eng_notation
from gnuradio.qtgui import Range, RangeWidget
import leo
from gnuradio import qtgui

class leo_channel(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "LEO channel simulation")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("LEO channel simulation")
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

        self.settings = Qt.QSettings("GNU Radio", "leo_channel")

        try:
            if StrictVersion(Qt.qVersion()) < StrictVersion("5.0.0"):
                self.restoreGeometry(self.settings.value("geometry").toByteArray())
            else:
                self.restoreGeometry(self.settings.value("geometry"))
        except:
            pass

        ##################################################
        # Variables
        ##################################################
        self.pointing_error = pointing_error = 1
        self.satellite_tx_antenna = satellite_tx_antenna = leo.quadrifilar_helix_antenna_make(6,435e6, 3, pointing_error, 0.5)
        self.satellite_rx_antenna = satellite_rx_antenna = leo.quadrifilar_helix_antenna_make(6,435e6, 3, pointing_error, 0.5)
        self.variable_satellite_0 = variable_satellite_0 = leo.satellite_make('ISS', '1 25544U 98067A   18268.52547184  .00016717  00000-0  10270-3 0  9019', '2 25544  51.6373 238.6885 0003885 206.9748 153.1203 15.53729445 14114', 435e6, 435e6, 27, satellite_tx_antenna, satellite_rx_antenna, 12, 190, 1200)
        self.tracker_tx_antenna = tracker_tx_antenna = leo.dipole_antenna_make(5, 145.8e6, 0, pointing_error)
        self.tracker_rx_antenna = tracker_rx_antenna = leo.quadrifilar_helix_antenna_make(6,435e6, 2, 0, 0.5)
        self.variable_tracker_0 = variable_tracker_0 = leo.tracker_make(variable_satellite_0, 35.3333, 25.1833, 1, '2018-09-25T15:48:25.0000000Z', '2018-09-25T15:58:35.0000000Z', 1000, 435E6, 435e6, 37, tracker_tx_antenna, tracker_rx_antenna, 1, 210, 19200)
        self.variable_leo_model_def_0 = variable_leo_model_def_0 = leo.leo_model_make(variable_tracker_0, 0, 5,
          													0, 7,
          													2, 4,
          													True, 7.5, 20, 90)
        self.samp_rate = samp_rate = 80e3

        ##################################################
        # Blocks
        ##################################################
        self.qtgui_waterfall_sink_x_0 = qtgui.waterfall_sink_c(
            4096, #size
            firdes.WIN_BLACKMAN_hARRIS, #wintype
            0, #fc
            samp_rate, #bw
            "", #name
            1 #number of inputs
        )
        self.qtgui_waterfall_sink_x_0.set_update_time(0.10)
        self.qtgui_waterfall_sink_x_0.enable_grid(False)
        self.qtgui_waterfall_sink_x_0.enable_axis_labels(True)



        labels = ['', '', '', '', '',
                  '', '', '', '', '']
        colors = [0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
                  1.0, 1.0, 1.0, 1.0, 1.0]

        for i in range(1):
            if len(labels[i]) == 0:
                self.qtgui_waterfall_sink_x_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_waterfall_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_waterfall_sink_x_0.set_color_map(i, colors[i])
            self.qtgui_waterfall_sink_x_0.set_line_alpha(i, alphas[i])

        self.qtgui_waterfall_sink_x_0.set_intensity_range(-140, 10)

        self._qtgui_waterfall_sink_x_0_win = sip.wrapinstance(self.qtgui_waterfall_sink_x_0.pyqwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_waterfall_sink_x_0_win)
        self.qtgui_freq_sink_x_0 = qtgui.freq_sink_c(
            4096, #size
            firdes.WIN_BLACKMAN_hARRIS, #wintype
            0, #fc
            samp_rate, #bw
            "", #name
            1
        )
        self.qtgui_freq_sink_x_0.set_update_time(0.10)
        self.qtgui_freq_sink_x_0.set_y_axis(-140, 10)
        self.qtgui_freq_sink_x_0.set_y_label('Relative Gain', 'dB')
        self.qtgui_freq_sink_x_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, 0.0, 0, "")
        self.qtgui_freq_sink_x_0.enable_autoscale(False)
        self.qtgui_freq_sink_x_0.enable_grid(False)
        self.qtgui_freq_sink_x_0.set_fft_average(1.0)
        self.qtgui_freq_sink_x_0.enable_axis_labels(True)
        self.qtgui_freq_sink_x_0.enable_control_panel(True)



        labels = ['', '', '', '', '',
            '', '', '', '', '']
        widths = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        colors = ["blue", "red", "green", "black", "cyan",
            "magenta", "yellow", "dark red", "dark green", "dark blue"]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0]

        for i in range(1):
            if len(labels[i]) == 0:
                self.qtgui_freq_sink_x_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_freq_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_freq_sink_x_0.set_line_width(i, widths[i])
            self.qtgui_freq_sink_x_0.set_line_color(i, colors[i])
            self.qtgui_freq_sink_x_0.set_line_alpha(i, alphas[i])

        self._qtgui_freq_sink_x_0_win = sip.wrapinstance(self.qtgui_freq_sink_x_0.pyqwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_freq_sink_x_0_win)
        self._pointing_error_range = Range(0, 90, 1, 1, 200)
        self._pointing_error_win = RangeWidget(self._pointing_error_range, self.set_pointing_error, 'pointing_error', "counter_slider", float)
        self.top_grid_layout.addWidget(self._pointing_error_win)
        self.leo_channel_model_0 = leo.channel_model(80e3, variable_leo_model_def_0, 1)
        self.analog_sig_source_x_1 = analog.sig_source_c(samp_rate, analog.GR_COS_WAVE, 1000, 1000, 0, 0)



        ##################################################
        # Connections
        ##################################################
        self.connect((self.analog_sig_source_x_1, 0), (self.leo_channel_model_0, 0))
        self.connect((self.leo_channel_model_0, 0), (self.qtgui_freq_sink_x_0, 0))
        self.connect((self.leo_channel_model_0, 0), (self.qtgui_waterfall_sink_x_0, 0))

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "leo_channel")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()

    def get_pointing_error(self):
        return self.pointing_error

    def set_pointing_error(self, pointing_error):
        self.pointing_error = pointing_error
        self.satellite_rx_antenna.set_pointing_error(self.pointing_error)
        self.satellite_tx_antenna.set_pointing_error(self.pointing_error)
        self.tracker_tx_antenna.set_pointing_error(self.pointing_error)

    def get_satellite_tx_antenna(self):
        return self.satellite_tx_antenna

    def set_satellite_tx_antenna(self, satellite_tx_antenna):
        self.satellite_tx_antenna = satellite_tx_antenna
        self.satellite_tx_antenna.set_pointing_error(self.pointing_error)

    def get_satellite_rx_antenna(self):
        return self.satellite_rx_antenna

    def set_satellite_rx_antenna(self, satellite_rx_antenna):
        self.satellite_rx_antenna = satellite_rx_antenna
        self.satellite_rx_antenna.set_pointing_error(self.pointing_error)

    def get_variable_satellite_0(self):
        return self.variable_satellite_0

    def set_variable_satellite_0(self, variable_satellite_0):
        self.variable_satellite_0 = variable_satellite_0

    def get_tracker_tx_antenna(self):
        return self.tracker_tx_antenna

    def set_tracker_tx_antenna(self, tracker_tx_antenna):
        self.tracker_tx_antenna = tracker_tx_antenna
        self.tracker_tx_antenna.set_pointing_error(self.pointing_error)

    def get_tracker_rx_antenna(self):
        return self.tracker_rx_antenna

    def set_tracker_rx_antenna(self, tracker_rx_antenna):
        self.tracker_rx_antenna = tracker_rx_antenna
        self.tracker_rx_antenna.set_pointing_error(0)

    def get_variable_tracker_0(self):
        return self.variable_tracker_0

    def set_variable_tracker_0(self, variable_tracker_0):
        self.variable_tracker_0 = variable_tracker_0

    def get_variable_leo_model_def_0(self):
        return self.variable_leo_model_def_0

    def set_variable_leo_model_def_0(self, variable_leo_model_def_0):
        self.variable_leo_model_def_0 = variable_leo_model_def_0

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.analog_sig_source_x_1.set_sampling_freq(self.samp_rate)
        self.qtgui_freq_sink_x_0.set_frequency_range(0, self.samp_rate)
        self.qtgui_waterfall_sink_x_0.set_frequency_range(0, self.samp_rate)



def main(top_block_cls=leo_channel, options=None):

    if StrictVersion("4.5.0") <= StrictVersion(Qt.qVersion()) < StrictVersion("5.0.0"):
        style = gr.prefs().get_string('qtgui', 'style', 'raster')
        Qt.QApplication.setGraphicsSystem(style)
    qapp = Qt.QApplication(sys.argv)

    tb = top_block_cls()
    tb.start()
    tb.show()

    def sig_handler(sig=None, frame=None):
        Qt.QApplication.quit()

    signal.signal(signal.SIGINT, sig_handler)
    signal.signal(signal.SIGTERM, sig_handler)

    timer = Qt.QTimer()
    timer.start(500)
    timer.timeout.connect(lambda: None)

    def quitting():
        tb.stop()
        tb.wait()
    qapp.aboutToQuit.connect(quitting)
    qapp.exec_()


if __name__ == '__main__':
    main()
