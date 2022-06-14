#!/usr/bin/env python
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Satellite pass prediction
# Author: Kostis Triantafyllakis (kostastriantaf@gmail.com)
# Description: gr-leo satellite pass prediction tool that uses C++ libSGP4
# Generated: Thu Nov  8 13:17:05 2018
##################################################

from gnuradio import eng_notation
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from optparse import OptionParser
import gnuradio.leo


class passpredict(gr.top_block):

    def __init__(self, tle_title='1 25544U 98067A   18268.52547184  .00016717  00000-0  10270-3 0  9019', tle_1='1 25544U 98067A   18268.52547184  .00016717  00000-0  10270-3 0  9019', tle_2='2 25544  51.6373 238.6885 0003885 206.9748 153.1203 15.53729445 14114', obs_start='2018-09-25T15:48:25.0000000Z', obs_end='2018-09-26T15:48:25.0000000Z', ground_station_longitude=25.1833, ground_station_latitude=35.3333, ground_station_altitude=1):
        gr.top_block.__init__(self, "Satellite pass prediction")

        ##################################################
        # Parameters
        ##################################################
        self.tle_title = tle_title
        self.tle_1 = tle_1
        self.tle_2 = tle_2
        self.obs_start = obs_start
        self.obs_end = obs_end
        self.ground_station_longitude = ground_station_longitude
        self.ground_station_latitude = ground_station_latitude
        self.ground_station_altitude = ground_station_altitude

        ##################################################
        # Variables
        ##################################################


        self.variable_tracker_0 = variable_tracker_0 = gnuradio.leo.tracker(tle_title, tle_1, tle_2, \
        ground_station_longitude, ground_station_latitude, ground_station_altitude, obs_start, obs_end)

        ##################################################
        # Blocks
        ##################################################



    def get_tle_title(self):
        return self.tle_title

    def set_tle_title(self, tle_title):
        self.tle_title = tle_title

    def get_tle_1(self):
        return self.tle_1

    def set_tle_1(self, tle_1):
        self.tle_1 = tle_1

    def get_tle_2(self):
        return self.tle_2

    def set_tle_2(self, tle_2):
        self.tle_2 = tle_2

    def get_obs_start(self):
        return self.obs_start

    def set_obs_start(self, obs_start):
        self.obs_start = obs_start

    def get_obs_end(self):
        return self.obs_end

    def set_obs_end(self, obs_end):
        self.obs_end = obs_end

    def get_ground_station_longitude(self):
        return self.ground_station_longitude

    def set_ground_station_longitude(self, ground_station_longitude):
        self.ground_station_longitude = ground_station_longitude

    def get_ground_station_latitude(self):
        return self.ground_station_latitude

    def set_ground_station_latitude(self, ground_station_latitude):
        self.ground_station_latitude = ground_station_latitude

    def get_ground_station_altitude(self):
        return self.ground_station_altitude

    def set_ground_station_altitude(self, ground_station_altitude):
        self.ground_station_altitude = ground_station_altitude



def argument_parser():
    description = 'A satellite pass prediction tool that uses C++ libSGP4'
    parser = OptionParser(usage="%prog: [options]", option_class=eng_option, description=description)
    parser.add_option(
        "", "--tle-title", dest="tle_title", type="string", default='1 25544U 98067A   18268.52547184  .00016717  00000-0  10270-3 0  9019',
        help="Set TLE TITLE [default=%default]")
    parser.add_option(
        "", "--tle-1", dest="tle_1", type="string", default='1 25544U 98067A   18268.52547184  .00016717  00000-0  10270-3 0  9019',
        help="Set TLE 1 [default=%default]")
    parser.add_option(
        "", "--tle-2", dest="tle_2", type="string", default='2 25544  51.6373 238.6885 0003885 206.9748 153.1203 15.53729445 14114',
        help="Set TLE 2 [default=%default]")
    parser.add_option(
        "", "--obs-start", dest="obs_start", type="string", default='2018-09-25T15:48:25.0000000Z',
        help="Set Observation Start [default=%default]")
    parser.add_option(
        "", "--obs-end", dest="obs_end", type="string", default='2018-09-26T15:48:25.0000000Z',
        help="Set Observation End [default=%default]")
    parser.add_option(
        "", "--ground-station-longitude", dest="ground_station_longitude", type="eng_float", default=eng_notation.num_to_str(25.1833),
        help="Set Ground station longitude [default=%default]")
    parser.add_option(
        "", "--ground-station-latitude", dest="ground_station_latitude", type="eng_float", default=eng_notation.num_to_str(35.3333),
        help="Set Ground station latitude [default=%default]")
    parser.add_option(
        "", "--ground-station-altitude", dest="ground_station_altitude", type="eng_float", default=eng_notation.num_to_str(1),
        help="Set Ground station altitude [default=%default]")
    return parser


def main(top_block_cls=passpredict, options=None):
    if options is None:
        options, _ = argument_parser().parse_args()

    tb = top_block_cls(tle_title=options.tle_title, tle_1=options.tle_1, tle_2=options.tle_2, obs_start=options.obs_start, obs_end=options.obs_end, ground_station_longitude=options.ground_station_longitude, ground_station_latitude=options.ground_station_latitude, ground_station_altitude=options.ground_station_altitude)
    tb.start()
    tb.wait()


if __name__ == '__main__':
    main()
