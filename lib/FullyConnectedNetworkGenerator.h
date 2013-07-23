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

#ifndef _LIBS_AGENT_FULLYCONNECTEDNETWORKGENERATOR
#define _LIBS_AGENT_FULLYCONNECTEDNETWORKGENERATOR

#include "AbstractNetworkGenerator.h"

namespace AgentLib { 

	//! Generates a fully connected network, where all edges have value 1.0, but no self-connections
	class FullyConnectedNetworkGenerator : public AbstractNetworkGenerator {
	public:

		//! specify the size of the network
		FullyConnectedNetworkGenerator(Number dimension):_dimension(dimension){}

		//! Required per base class
		virtual ~FullyConnectedNetworkGenerator();

		//! All edges have always value 1.0
		virtual double CreateEdge(Index i, Index j) const {return 1.0;}

		//! Size of the network
		virtual Number Dimension() const { return _dimension; }

	private:

		Number _dimension;

	};

	inline FullyConnectedNetworkGenerator::~FullyConnectedNetworkGenerator(){
	}
}

#endif // include guard

