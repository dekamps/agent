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

#ifndef _LIBS_AGENT_CHARTIST
#define _LIBS_AGENT_CHARTIST

#include "AgentProperty.h"
#include "Trader.h"

namespace AgentLib {

	//! class represents a chartist trader; it distringuishes itself from other traders
	//! by the way of its price formation given recent and past prices in the network.

	class Chartist : public Trader {
	public:

		Chartist
		(
			const Network&,			//! network through which price information is communicated
			Index,					//! position of this trader in the network
			const AgentProperty&	//! properties of this agent
		);

		virtual ~Chartist();
	};

}

#endif // include guard
