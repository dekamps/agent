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

using namespace AgentLib;

Chartist::Chartist
(
	const Network&				net,
	Index						i,
	const AgentProperty&		prop,
	const Trader::VectorTrader& vec_trad
):
Trader(net,i,prop,vec_trad)
{
}

Chartist::~Chartist()
{
}

void Chartist::Update(Index t)
{
	double deltaP = _var._price - _var._last_price;
	_var._last_price = _var._price;
	_var._estimate = _var._estimate + _prop._c*(deltaP-_var._estimate);
	double x = _var._estimate - _prop._bond_return;
	_var._demand = 1.0/(1+exp(-4*_prop._b*x)) - 0.5;
 
}
