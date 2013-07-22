project( AgentLib )

if( WIN32 )
  find_package( WINGSL REQUIRED )
  if( NOT GSL_FOUND )
    message( FATAL_ERROR "WinGsl not found (module AgentLib lib)." )
  endif( NOT GSL_FOUND )
  link_directories( ${GSL_LIBRARY_DIRS} )
  set(LIB_TYPE STATIC)
else( WIN32 )
  set( LIB_TYPE SHARED )
  link_directories( ${GSL_LIBRARY_DIRS} )
endif( WIN32 )

include_directories( ${GSL_INCLUDE_DIR} )

set( lib_SRC#
     Chartist.cpp
	 Fundamentalist.cpp
     Network.cpp
	 NetworkSimulation.cpp
	 RandomNetGenerator.cpp
	 SimulationParameter.cpp
	 Trader.cpp
 )

set( lib_HEADERS
     AbstractNetworkGenerator.h
	 AgentLib.h
	 AgentProperty.h
	 BasicDefinitions.h
	 Chartist.h
	 Fundamentalist.h
	 FullyConnectedNetworkGenerator.h
     Network.h
	 NetworkSimulation.h
	 RandomNetGenerator.h
	 SimulationParameter.h
	 Trader.h
	 TraderVariables.h
 )

add_library( AgentLib ${LIB_TYPE} ${lib_SRC} ${lib_HEADERS})
set_target_properties(AgentLib PROPERTIES LINKER_LANGUAGE CXX)

#target_link_libraries( agent
#  )

