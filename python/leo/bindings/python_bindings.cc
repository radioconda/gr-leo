/*
 * Copyright 2020 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <pybind11/pybind11.h>

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/arrayobject.h>

namespace py = pybind11;

// Headers for binding functions
/**************************************/
// The following comment block is used for
// gr_modtool to insert function prototypes
// Please do not delete
/**************************************/
// BINDING_FUNCTION_PROTOTYPES(
void bind_leo_types(py::module& m);
void bind_generic_antenna(py::module& m);
void bind_yagi_antenna(py::module& m);
void bind_custom_antenna(py::module& m);
void bind_helix_antenna(py::module& m);
void bind_dipole_antenna(py::module& m);
void bind_monopole_antenna(py::module& m);
void bind_parabolic_reflector_antenna(py::module& m);
void bind_quadrifilar_helix_antenna(py::module& m);
void bind_satellite(py::module& m);
void bind_tracker(py::module& m);
void bind_generic_attenuation(py::module& m);
void bind_atmospheric_gases_itu(py::module& m);
void bind_atmospheric_gases_regression(py::module& m);
void bind_free_space_path_loss(py::module& m);
void bind_precipitation_itu(py::module& m);
void bind_generic_noise(py::module& m);
void bind_white_gaussian_noise(py::module& m);
void bind_antenna_pointing_loss(py::module& m);
void bind_link_margin(py::module& m);
void bind_generic_model(py::module& m);
void bind_leo_model(py::module& m);
void bind_channel_model(py::module& m);
// ) END BINDING_FUNCTION_PROTOTYPES


// We need this hack because import_array() returns NULL
// for newer Python versions.
// This function is also necessary because it ensures access to the C API
// and removes a warning.
void* init_numpy()
{
    import_array();
    return NULL;
}

PYBIND11_MODULE(leo_python, m)
{
    // Initialize the numpy C API
    // (otherwise we will see segmentation faults)
    init_numpy();

    // Allow access to base block methods
    py::module::import("gnuradio.gr");

    /**************************************/
    // The following comment block is used for
    // gr_modtool to insert binding function calls
    // Please do not delete
    /**************************************/
    // BINDING_FUNCTION_CALLS(
    bind_leo_types(m);
    bind_generic_antenna(m);
    bind_yagi_antenna(m);
    bind_custom_antenna(m);
    bind_helix_antenna(m);
    bind_dipole_antenna(m);
    bind_monopole_antenna(m);
    bind_parabolic_reflector_antenna(m);
    bind_quadrifilar_helix_antenna(m);
    bind_satellite(m);
    bind_tracker(m);
    bind_generic_attenuation(m);
    bind_atmospheric_gases_itu(m);
    bind_atmospheric_gases_regression(m);
    bind_free_space_path_loss(m);
    bind_precipitation_itu(m);
    bind_generic_noise(m);
    bind_white_gaussian_noise(m);
    bind_antenna_pointing_loss(m);
    bind_link_margin(m);
    bind_generic_model(m);
    bind_leo_model(m);
    bind_channel_model(m);
    // ) END BINDING_FUNCTION_CALLS
}
