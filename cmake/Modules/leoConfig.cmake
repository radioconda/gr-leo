INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_LEO leo)

FIND_PATH(
    LEO_INCLUDE_DIRS
    NAMES leo/api.h
    HINTS $ENV{LEO_DIR}/include
        ${PC_LEO_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    LEO_LIBRARIES
    NAMES gnuradio-leo
    HINTS $ENV{LEO_DIR}/lib
        ${PC_LEO_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LEO DEFAULT_MSG LEO_LIBRARIES LEO_INCLUDE_DIRS)
MARK_AS_ADVANCED(LEO_LIBRARIES LEO_INCLUDE_DIRS)

