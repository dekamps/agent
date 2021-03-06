/*
* Copyright (c) 2013 Dan Ladley, Marc de Kamps <M.deKamps@leeds.ac.uk>
*
* Permission to use, copy, modify, and distribute this software for any
* purpose with or without fee is hereby granted, provided that the above
* copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
* ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
* ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
* OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#ifndef _LIBS_AGENT_NETWORKSIMULATION
#define _LIBS_AGENT_NETWORKSIMUALTION

#include <vector>
#include <boost/shared_ptr.hpp>
#include "AgentProperty.h"
#include "BasicDefinitions.h"
#include "Network.h"
#include "NetworkState.h"
#include "SimulationParameter.h"
#include "Trader.h"

namespace AgentLib {

	//! This class simulates one session of trading on a given network.
	class NetworkSimulation {
	public:

		//! Use this constructor if the placement of the fundamentalists and the chartists is random, or does not matter.
	
		NetworkSimulation
		(
			const Network&,			//! network graph on which the simulation will run
			Number,					//! number of chartists
			Number,					//! number of fundamentalists,
			const AgentProperty&	//! properties shared by all agents in the network
		);

		//! configure a simulation
		void Configure(const SimulationParameter&);

		//! run a simulation
		void Run();

	private:

		NetworkState			_state;
		Trader::VectorTrader	_vec_trader;
		SimulationParameter		_par_sim;
	};

}

#endif // include guard