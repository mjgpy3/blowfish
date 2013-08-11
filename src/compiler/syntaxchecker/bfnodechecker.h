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

#ifndef BLOWFISH_NODE_CHECKER
#define BLOWFISH_NODE_CHECKER

#include "bfnodes.h"
#include "bftokennames.h"
#include <vector>
using namespace std;

bool childrenAreExactly(BfNode * node, TokenName types[]);
bool isOperator(BfNode * node);
bool isOperatorToken(TokenName name);
bool isLiteral(BfNode * node);
bool isLiteralToken(TokenName name);
bool isAssignment(BfNode * node);
bool isAssignmentToken(TokenName name);
bool isNegativeLiteral(BfNode * node, TokenName name);
bool isNegativeLiteralToken(TokenName name);
bool impliesScope(BfNode * node);
bool tokenImpliesScope(TokenName name);
bool haveSameNodeStructure(BfNode * aNode, BfNode * anotherNode);
bool isChildlessNode(BfNode * node);
bool isChildlessNodeToken(TokenName name);
bool becomesCurrentNode(BfNode * node);
bool becomesCurrentNodeToken(TokenName name);
	
#endif
