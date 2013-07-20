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
#ifndef _LIBS_AGENT_ABSTRACTNETWORKGENERATOR
#define _LIBS_AGENT_ABSTRACTNETWORKGENERATOR

#include "BasicDefinitions.h"

namespace Agent {

	//! A NetworkGenerator object is able to accept the relevant parameters, and to determine what each individual edge
	//! should be in the network. So the Network saves mainly as a representation, which is created by an object of type
	//! AbstractNetworkGenerator

	class AbstractNetworkGenerator {

		//! virtual base class
		virtual ~AbstractNetworkGenerator() = 0;

		//! create specific edges
		virtual void CreateEdge(Index, Index);
	};
}

#endif // include guard