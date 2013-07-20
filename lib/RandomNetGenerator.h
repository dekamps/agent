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

#ifndef _LIBS_AGENT_RANDOMNETWORKGENERATOR
#define _LIBS_AGENT_RANDOMNETWORKGENERATOR

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include "AbstractNetworkGenerator.h"

using namespace boost::numeric::ublas;

namespace AgentLib {

	//! Generates a random network structure. Two parameters are required: the size of the network in terms of
	//! number of nodes, and the number of connections we allow in the network.

	//! Networks are randomly generated; if a network is not totally connected it is discarded. The generation 
	//! process is repeated until a connected network is realized.

	class RandomNetGenerator : public AbstractNetworkGenerator {
	public:

		//! constructor
		RandomNetGenerator
		(
			Number,		//! Number of nodes in the network
			Number		//! Total number of connections in the network (must be smaller than N*(N-1)/2)
		);

		//! virtual destructor, required for base class.
		virtual ~RandomNetGenerator();

		//! Edge values.
		virtual double CreateEdge(Index, Index) const;

		//! Number of nodes in the network.
		virtual Number Dimension() const;

	private:

		void GenerateMatrix(matrix<double>*);
		bool IsMatrixConnected(const matrix<double>& );

		matrix<double> _m;

	};


}


#endif // include guard
