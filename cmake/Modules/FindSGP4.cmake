INCLUDE(FindPkgConfig)

FIND_PATH(
    SGP4_INCLUDE_DIRS
    NAMES SGP4
    HINTS $ENV{SGP4_DIR}/include/SGP4/
        ${PC_SGP4_INCLUDEDIR}
    PATHS /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    SGP4_LIBRARIES
    NAMES sgp4s
    HINTS $ENV{SGP4_DIR}/lib
        ${PC_SGP4_LIBDIR}
    PATHS /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SGP4 DEFAULT_MSG SGP4_LIBRARIES SGP4_INCLUDE_DIRS)
