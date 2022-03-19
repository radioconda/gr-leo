# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT leo_sources)
    MESSAGE(STATUS "No C++ sources... skipping python bindings")
    return()
endif(NOT leo_sources)

########################################################################
# Check for pygccxml
########################################################################
GR_PYTHON_CHECK_MODULE_RAW(
    "pygccxml"
    "import pygccxml"
    PYGCCXML_FOUND
    )

include(GrPybind)

########################################################################
# Python Bindings
########################################################################

list(APPEND leo_python_files
    python_bindings.cc
    generic_antenna_python.cc
    yagi_antenna_python.cc
    custom_antenna_python.cc
    helix_antenna_python.cc
    dipole_antenna_python.cc
    monopole_antenna_python.cc
    parabolic_reflector_antenna_python.cc
    quadrifilar_helix_antenna_python.cc
    satellite_python.cc
    tracker_python.cc
    generic_attenuation_python.cc
    atmospheric_gases_itu_python.cc
    atmospheric_gases_regression_python.cc
    free_space_path_loss_python.cc
    precipitation_itu_python.cc
    generic_noise_python.cc
    white_gaussian_noise_python.cc
    antenna_pointing_loss_python.cc
    link_margin_python.cc
    generic_model_python.cc
    leo_model_python.cc
    channel_model_python.cc
  )

GR_PYBIND_MAKE_OOT(leo
   ../../..
   gr::leo
   "${leo_python_files}")

# copy in bindings .so file for use in QA test module
add_custom_target(
  copy_bindings_for_tests ALL
  COMMAND
    ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/*.so"
    ${CMAKE_BINARY_DIR}/test_modules/gnuradio/leo/
  DEPENDS leo_python)

install(TARGETS leo_python DESTINATION ${GR_PYTHON_DIR}/gnuradio/leo COMPONENT pythonapi)
