########################################################################
# Project setup
########################################################################
cmake_minimum_required(VERSION 2.8)
project(SGP4)

# Select the release build type by default to get optimization flags
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
    message(STATUS "Build type not specified: defaulting to release.")
endif(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

if(NOT LIB_INSTALL_DIR)
    set(LIB_INSTALL_DIR lib)
endif()

set(libsgp4_sources
    CoordGeodetic.cpp
    CoordTopocentric.cpp
    DateTime.cpp
    DecayedException.cpp
    Eci.cpp
    Globals.cpp
    Observer.cpp
    OrbitalElements.cpp
    SGP4.cpp
    SatelliteException.cpp
    SolarPosition.cpp
    TimeSpan.cpp
    Tle.cpp
    TleException.cpp
    Util.cpp
    Vector.cpp)

set(libsgp4_includes
    CoordGeodetic.h
    CoordTopocentric.h
    DateTime.h
    DecayedException.h
    Eci.h
    Globals.h
    Observer.h
    OrbitalElements.h
    SatelliteException.h
    SGP4.h
    SolarPosition.h
    TimeSpan.h
    TleException.h
    Tle.h
    Util.h
    Vector.h)

add_library(sgp4 SHARED ${libsgp4_sources} ${libsgp4_includes})
set_property(TARGET sgp4 PROPERTY IMPORTED_LOCATION ${install_dir}/libsgp4.so)

########################################################################
# Create uninstall target
########################################################################
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
