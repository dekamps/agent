if( WIN32 )
  find_package( WINGSL REQUIRED )
  if( NOT GSL_FOUND )
    message( FATAL_ERROR "WinGsl not found (module AgentLib apps)." )
  endif( NOT GSL_FOUND )
    link_directories( ${GSL_LIBRARY_DIRS} )
else( WIN32 )
    find_package( GSL )
    link_directories( ${GSL_LIBRARY_DIRS} )
endif( WIN32 )

include_directories( ${GSL_INCLUDE_DIR} )
link_directories( ${GSL_LIBRARY_DIR} )

include_directories( ../../lib )


if ( Boost_FOUND )
    include_directories( ${Boost_INCLUDE_DIRS} )
    link_directories( ${Boost_LIBRARY_DIRS} )
    if (UNIX)
        ADD_DEFINITIONS("-fno-strict-aliasing" )
    endif (UNIX)
    set ( LIBLIST 
        AgentLib
        ${gsl_LINK_FLAGS} 
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    )
else( Boost_FOUND)
    message( STATUS "Boost.TEST not found -- skipping the BOOST unit tests" )
endif ( Boost_FOUND )

add_executable( DanOrig1 
		main2.cc )

add_executable( DanOrig2
		individual5.cc )


add_executable( SmallTest
		mainsmall.cpp )

add_executable( UnitAgentLib
		UnitAgentLib.cpp
		NetworkSimulationTest.cpp
		 )		

target_link_libraries( UnitAgentLib ${LIBLIST} )

if (WIN32)
target_link_libraries( UnitAgentLib debug ${GSL_LIBRARY_DEBUG_DIRS}/gsl.lib debug ${GSL_LIBRARY_DEBUG_DIRS}/cblas.lib )
target_link_libraries( UnitAgentLib optimized ${GSL_LIBRARY_RELEASE_DIRS}/gsl.lib optimized ${GSL_LIBRARY_RELEASE_DIRS}/cblas.lib )
else (WIN32)
target_link_libraries( UnitAgentLib gsl ${GSLPREFIX}cblas )
endif (WIN32)
