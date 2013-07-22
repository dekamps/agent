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

#ifndef _LIBS_AGENT_TRADER
#define _LIBS_AGENT_TRADER

#include <boost/shared_ptr.hpp>
#include "AgentProperty.h"
#include "BasicDefinitions.h"
#include "Network.h"
#include "TraderVariables.h"

namespace AgentLib {

	//! Common base class for traders. The network does not know about what kind of Trader an agent is. The Trader is responsible
	//! for determining its own price estimate. This is handled in the subclasses of this class.

	class Trader {
	public:

		 typedef std::vector<boost::shared_ptr<Trader> > VectorTrader;

		//! A trader must know about the network it is embedded in. It must also know about its position in the network.
		Trader
		(
			const Network&, 
			Index,
			const AgentProperty&,
			const VectorTrader&
		);

		//! virtual destructor for all Trader classes
		virtual ~Trader() = 0;

		//! Common updates for arr traders in the network, but different from shout
		virtual void Update(Time) = 0;

		//! An individual trader can recalculate its price and shout.
		virtual void Shout(Time);

		//! Adapt prices
		virtual void AdaptPrice(Time);

		//! Number of Trader s connected to this one
		Number NumberOfConnections() const;

		Index Id() const { return _i_pos_in_net; }

	protected:

		const Network&		_net;
		const Index			_i_pos_in_net;
		const AgentProperty	_prop;
		TraderVariables		_var;
		std::vector<double>	_demandsP;

		const VectorTrader& _vec_trader; 
	};
}

#endif // include guard