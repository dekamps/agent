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
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE AgentLib
#include <boost/test/unit_test.hpp>
#include "../lib/AgentLib.h"

using namespace AgentLib;



BOOST_AUTO_TEST_CASE(NetworkSimulationCreationTest)
{
	FullyConnectedNetworkGenerator gen(4);
	Network net(gen);

	AgentProperty prop;

	prop._a = 0.3;
	prop._b = 0.5;
	prop._c = 1.5;

	NetworkSimulation
		sim
		(
			net,
			2,
			2,
			prop
		);
}

BOOST_AUTO_TEST_CASE(SingleSimulationTest)
{
	SimulationParameter par_sim(0,1000);

	FullyConnectedNetworkGenerator gen(2);
	Network net(gen);


	AgentProperty prop;

	prop._a = 0.3;
	prop._b = 0.5;
	prop._c = 1.5;
	prop._initial_price = 0.505;
	prop._asset_value   = 0.5;
	prop._bond_return   = 0.0;

	NetworkSimulation
		sim
		(
			net,
			1,
			1,
			prop
		);

	SimulationParameter
		par
		(
			0,
			10000
		);

	sim.Configure(par);

	sim.Run();
}