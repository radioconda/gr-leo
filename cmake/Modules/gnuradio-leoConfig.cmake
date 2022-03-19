find_package(PkgConfig)

PKG_CHECK_MODULES(PC_GR_LEO gnuradio-leo)

FIND_PATH(
    GR_LEO_INCLUDE_DIRS
    NAMES gnuradio/leo/api.h
    HINTS $ENV{LEO_DIR}/include
        ${PC_LEO_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_LEO_LIBRARIES
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

include("${CMAKE_CURRENT_LIST_DIR}/gnuradio-leoTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_LEO DEFAULT_MSG GR_LEO_LIBRARIES GR_LEO_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_LEO_LIBRARIES GR_LEO_INCLUDE_DIRS)
