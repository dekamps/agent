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

#include "Chartist.h"
#include "Fundamentalist.h"
#include "NetworkSimulation.h"

using namespace AgentLib;

NetworkSimulation::NetworkSimulation
(
	const Network&			net,
	Number					n_chart,
	Number					n_fund,
	const AgentProperty&	prop
)
{
	for (Index i = 0; i < n_chart; i++)
		_vec_trader.push_back( boost::shared_ptr<Trader>(new Chartist(net,i,prop)));
	for (Index j = 0; j < n_chart; j++)
		_vec_trader.push_back( boost::shared_ptr<Trader>(new Fundamentalist(net,n_chart + j, prop)));
}