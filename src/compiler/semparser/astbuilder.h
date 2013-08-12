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

#ifndef BLOWFISH_AST_BUILDER
#define BLOWFISH_AST_BUILDER

#include "bfnodes.h"
#include "foundtoken.h"
#include "bfscopenode.h"
#include "bftokennames.h"
#include "bflexer.h"
#include <vector>
using namespace std;

class AstBuilder
{
public:
	AstBuilder();
	BfNode * buildAst(vector<FoundToken> tokens);
	void buildNode(FoundToken tok);

	void insertOperatorNode(BfBinaryOperator * n);
	void insertAssignmentNode(BfAssignment * n);
	void attachChild(BfNode * n);
	void attachChildAsCurrent(BfNode * n);
	void attachNegativeChild(BfNode * n);
	void moveToCurrentChild();
	void moveToParent();
	void currentChildIsChildOf(BfNode * n);
	void currentChildrenAreChildrenOf(BfNode * n, TokenName until);
	void currentBlockDefinesNewScope();

private:
	BfNode * root;
	BfNode * current;
	vector<TokenName> ignoreNewlineStack;
	TokenName lastToken;
	vector<BfScopeNode*> scopeStack;
	BfScopeNode * nextScope;
	bool nextIdentifierNamesScope;
};

#endif
