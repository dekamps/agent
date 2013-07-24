PROJECT(Agent)

cmake_minimum_required(VERSION 2.8)
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake-modules )

set(LIBTYPE shared)

if( WIN32 )
  find_package( WINGSL REQUIRED )
  if( NOT GSL_FOUND )
    message( FATAL_ERROR "WinGsl not found (module AgentLib top)." )
  endif( NOT GSL_FOUND )
    link_directories( ${GSL_LIBRARY_DIRS} )
else( WIN32 )
    set (GSLPREFIX gsl)
    find_package( GSL )
    link_directories( ${GSL_LIBRARY_DIRS} )
endif( WIN32 )

include_directories( ${GSL_INCLUDE_DIR} )
link_directories( ${GSL_LIBRARY_DIR} )


find_package( Boost COMPONENTS unit_test_framework program_options)
if ( Boost_FOUND )
    include_directories( ${Boost_INCLUDE_DIRS} )
    link_directories( ${Boost_LIBRARY_DIRS} )
    if (UNIX)
        ADD_DEFINITIONS("-fno-strict-aliasing" )
    endif (UNIX)
    set ( LIBLIST 
        ${gsl_LINK_FLAGS} 
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    )
else( Boost_FOUND)
    message( STATUS "Boost.TEST not found -- skipping the BOOST unit tests" )
endif ( Boost_FOUND )

add_subdirectory(./lib)
add_subdirectory(./apps)
