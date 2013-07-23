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

#include <iostream>
#include <boost/foreach.hpp>
#include "Trader.h"

using namespace AgentLib;
using namespace std;

Trader::Trader
(
	const Network&			net,
	Index					i,
	const AgentProperty&	prop,
	const VectorTrader&		vec_trader
):
_net(net),
_i_pos_in_net(i),
_prop(prop),
_var
(
0.0,
prop._initial_price,
prop._initial_price,
0.0
),
_demandsP(net.Dimension(),0.0),
_vec_trader(vec_trader)
{
}

Trader::~Trader()
{
}


Number Trader::NumberOfConnections() const
{
	Index predecs = 0;
	for( Index j = 0; j < _net.Dimension(); j++)
		predecs += static_cast<int>(_net(this->_i_pos_in_net,j));

	return predecs;
}

void Trader::Shout(Time t)
{
	double demand = 0;
	int predecs = NumberOfConnections();

	for( Index j = 0; j < _net.Dimension(); j++){
		if ( _net(this->_i_pos_in_net, j) != 0.0){
			demand += _demandsP[j];
			_demandsP[j] = 0;
		}
	}
	_var._price += demand/predecs;

	cout << this->Id() << " " << _var._price << endl;

 /*   for(int i  = 0; i < TRADERS; i++)
            if(connections[choice][i]==1)// && i != choice)
            {
               demand += demandsP[choice][i];
               demandsP[choice][i] = 0;
            }
            //if(connections[choice][i]==1 && i != choice)
            //   demand += demands[i];
          prices[choice] += demand/(counts[choice]);
 */    
}

void Trader::AdaptPrice(Time t)
{
	for (Index i = 0; i < _vec_trader.size(); i++)
		_demandsP[i] += _var._demand;
}
/*
{
       for(int i = 0; i <TRADERS; i++)
          demandsP[i][choice] += demands[choice];
}*/