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
#include <cassert>
#include "RandomNetGenerator.h"

using namespace AgentLib;

void RandomNetGenerator::GenerateMatrix(matrix<double>* p_mat){
	matrix<double>& m = *p_mat;
	Number n_connections = p_mat->size1();

	// This is Dan's code from main.cpp
	   // first set all connections to 0 except self-connections, which are 1
	for(Index i = 0; i < n_connections; i++)
		for(Index j = 0; j < n_connections; j++)
			m(i,j) = (i == j) ? 1.0 : 0.0; 
	Number count = 0;

	// then randomly add 2*M symmetric connections
	while(count < n_connections){  
		int x = (int)(n_connections*(rand()/(RAND_MAX+1.0)));
		int y = (int)(n_connections*(rand()/(RAND_MAX+1.0)));
	    if( m(x,y) == 0.0){
			count++;
	          m(x,y)=1.0;
		      m(y,x)=1.0;
			}
	}
}

bool RandomNetGenerator::IsMatrixConnected(const matrix<double>& m)
{
	Number n_nodes = m.size1();

	// now check whether all traders are connected, and if not, completely redo the generation
	vector<bool> reached(n_nodes, false);
	vector<bool> toCheck(n_nodes, false);

	toCheck[0] = true;
	int needChecking = 1;
	Number found = 0;
	while(needChecking > 0 && found < n_nodes)
	{
		int choice = 0;
		while(toCheck[choice] == false)
			choice++;
		needChecking--;
		toCheck[choice] = false;
		found++;
		reached[choice] = true;
		for(Index i = 0; i < n_nodes; i++)
			if(_m(choice,i) == 1)
				if(reached[i] == false && toCheck[i] == false)
				{
					needChecking++;
					toCheck[i] = true;
				}
	}

	return (found == n_nodes) ? true : false;
}

RandomNetGenerator::RandomNetGenerator
(
	Number n_nodes,
	Number n_connections
):
_m(n_nodes,n_nodes)
{
	this->GenerateMatrix(&_m);
	while(! this->IsMatrixConnected(_m) )
		this->GenerateMatrix(&_m);
}


RandomNetGenerator::~RandomNetGenerator(){
}

Number RandomNetGenerator::Dimension() const
{
	return _m.size1();
}

double RandomNetGenerator::CreateEdge(Index i, Index j) const
{
	assert( i  < _m.size1() );
	assert( j  < _m.size2() );

	return _m(i,j);
}
