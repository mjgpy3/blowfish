/*
  Copyright (C) 2013 Michael Gilliland

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "bfexecutor.h"
#include "bfnodechecker.h"
#include "bfnodes.h"
#include "bfscopenode.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void BfExecutor::executeAst(BfNode * astToExecute)
{
	if ( !isRoot( astToExecute ) )
	{
		executorError( "AST must begin with a proper blowfish root node" );
	}

	astRoot = astToExecute;

	scopeStack.push_back( astRoot->getScope() );

	for (int i = 0; i < astRoot->numChildren(); i += 1)
	{
		currentNode = astRoot->child( i );

		if ( isOperator( currentNode) )
		{
			currentNumber = executeMathOperator( currentNode );
		}
	}
}

BfNumber * BfExecutor::executeMathOperator(BfNode * node)
{
	if (node->getTypeId() == t_integer)
	{
		return new BfIntegerNumber(node->getValue());
	}
	else if (node->getTypeId() == t_float)
	{
		return new BfFloatNumber(node->getValue());
	}
	else if (node->getTypeId() == t_op_plus)
	{
		return add( 
			executeMathOperator( node->child(0) ),
			executeMathOperator( node->child(1) ) );
	}
}

void executorError(string message)
{
	cout << "blowfish execution error:" << endl;
	cout << message << endl;
	exit(1);
}
