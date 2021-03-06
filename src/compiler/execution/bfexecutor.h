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

#ifndef BLOWFISH_EXECUTOR
#define BLOWFISH_EXECUTOR

#include "bfclass.h"
#include "bfnodes.h"
#include "bfnumber.h"
#include "bfparams.h"
#include "bfscopenode.h"
#include "instancebuilder.h"
#include <string>
#include <vector>
using namespace std;

class BfExecutor
{
public:
	void executeAst(BfNode * astToExecute);
	BfNumber * currentNumber;
	BfScopeNode * currentScope;
	BfObject * tryPerformCall(BfObject * obj, string methodName, BfParams * params);

private:
	BfObject * executeOperator(BfNode * node);
	vector<BfScopeNode*> scopeStack;
	BfNode * currentNode;
	BfNode * astRoot;
	InstanceBuilder * instanceBuilder;

	string getIdentifierName( BfNode * node );
};

void executorError(string message);

#endif
