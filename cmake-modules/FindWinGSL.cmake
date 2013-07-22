#
# Find the windows gsl library
#
# lets guess some typical root dirs for wingsl

SET(GSL_POSSIBLE_ROOT_DIRS
    "${GSL_ROOT_DIR}"
    "$ENV{GSL_ROOT_DIR}"
    "C:/gsl"
    "C:/gsl-1.15"
    "$ENV{ProgramFiles}"
    )


FIND_PATH( GSL_ROOT_DIR
    NAMES
    "gsl"
    PATHS ${GSL_POSSIBLE_ROOT_DIRS}
    )

FIND_PATH( GSL_INCLUDE_DIR
    NAMES
    gsl_mode.h
    PATHS ${GSL_ROOT_DIR}
    )

SET(GSL_LIBDIR_SUFFIXES
    lib
    )


FIND_PATH( GSL_LIBRARY_DEBUG_DIRS
    NAMES
    "gsl.lib"
    PATHS "${GSL_ROOT_DIR}/build.vc10/ddl/Win32/Debug"
    )



FIND_PATH( GSL_LIBRARY_RELEASE_DIRS
    NAMES
    "gsl.lib"
    PATHS "${GSL_ROOT_DIR}/build.vc10/ddl/Win32/Release"
    )


if( GSL_INCLUDE_DIR AND GSL_LIBRARY_DEBUG_DIRS )
    set( GSL_FOUND TRUE )
    set( ENV{GSL_INCLUDE_DIR ${GSL_INCLUDE_DIR} )
    set( ENV{GSL_LIBRARY_DEBUG_DIRS} GSL_LIBRARY_DEBUG_DIRS} )
endif( GSL_INCLUDE_DIR AND GSL_LIBRARY_DEBUG_DIRS )

if (GSL_INCLUDE_DIR AND GSL_LIBRARY_DEBUG_DIRS )
    set( GSL_FOUND TRUE )
    set( ENV{GSL_INCLUDE_DIR} ${GSL_INCLUDE_DIR} )
    set( ENV{GSL_LIBRARY_RELEASE_DIRS} GSL_LIBRARY_RELEASE_DIRS} )
endif (GSL_INCLUDE_DIR AND GSL_LIBRARY_DEBUG_DIRS )

if( GSL_FOUND )
    add_definitions( -DHAVE_GSL )
endif( GSL_FOUND )


