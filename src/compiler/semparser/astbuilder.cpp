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

#include <iostream>
#include "astbuilder.h"
#include "bflexer.h"
#include "bfnodechecker.h"
#include "bfnodefactory.h"
#include "bfnodes.h"
#include "foundtoken.h"
using namespace std;

AstBuilder::AstBuilder()
{
	// The global namespace, BfRoot
	BfNode * blowfish = new BfRoot(); 
	BfScopeNode * globalScope = new BfScopeNode("blowfish");

	blowfish->attachScope(globalScope);
	scopeStack.push_back(globalScope);

	root = blowfish;
	current = root;

	nextScope = new BfScopeNode();
	nextIdentifierNamesScope = false;
}

void AstBuilder::fixFloatErrors(vector<FoundToken> tokens, int i)
{
	Token newToken;
	newToken.type = tokens[i].getTokenValue() == t_float ? t_integer : t_neg_integer;

	string value  = tokens[i].getValue().substr(0, tokens[i].getValue().length()-1);
	
	FoundToken newIntToken = FoundToken(newToken, value);

	buildNode(newIntToken);
}

bool AstBuilder::isMissInformedFloat(vector<FoundToken> tokens, int i)
{
	return (tokens[i].getTokenValue() == t_neg_float || tokens[i].getTokenValue() == t_float) &&
		tokens.size() > i+1 &&
		tokens[i+1].getTokenValue() == t_identifier &&
		*(tokens[i].getValue()).rbegin() == '.';
}

BfNode * AstBuilder::buildAst(vector<FoundToken> tokens)
{
	for (int i = 0; i < tokens.size(); i += 1)
	{
		if (isMissInformedFloat(tokens, i))
		{
			fixFloatErrors(tokens, i);
			i += 1;
		}

		buildNode(tokens[i]);
	}

	return root;
}

void AstBuilder::buildNode(FoundToken tok)
{
	TokenName currentToken = tok.getTokenValue();

	if (ignoreNewlineStack.size() != 0 && currentToken == ignoreNewlineStack.back())
	{
		ignoreNewlineStack.pop_back();
	}

	if (isOperatorToken(currentToken))
	{
		insertOperatorNode(
			 BfOperatorNodeFactory(currentToken) );
	}
	else if (isAssignmentToken(currentToken))
	{
		insertAssignmentNode(
			BfAssignmentNodeFactory(currentToken) );
	}
	else if (isLiteralToken(currentToken))
	{
		attachChild(
			BfLiteralNodeFactory(currentToken, tok.getValue()) );
	}
	else if (isNegativeLiteralToken(currentToken))
	{
		attachNegativeChild(
			BfNegativeLiteralFactory(currentToken, tok.getValue()) );
	}
	else if (tokenImpliesScope(currentToken))
	{
		attachChildAsCurrent(
			BfBlockStarterNodeFactory(currentToken) );

		ignoreNewlineStack.push_back(t_block_begin);

		if (tokenImpliesNamedScope(currentToken))
		{
			nextIdentifierNamesScope = true;
		}
	}
	else if (isChildlessNodeToken(currentToken))
	{
		attachChild(
			BfChildlessNodeFactory(currentToken, tok.getValue()) );

		if (nextIdentifierNamesScope && currentToken == t_identifier)
		{
			nextScope->setName(tok.getValue());
			nextIdentifierNamesScope = false;
		}
	}
	else if (becomesCurrentNodeToken(currentToken))
	{
		attachChildAsCurrent(
			BfBecomesCurrentNodeFactory(currentToken) );
	}
	else if (currentToken == t_paran_begin)
	{
		attachChildAsCurrent(
			new BfExpression() );
	}
	else if (currentToken == t_holder_begin)
	{
		attachChildAsCurrent(
			BfHolderFactory(tok.getValue().substr(0, 1)) );

		ignoreNewlineStack.push_back(t_holder_end);
	}
	else if (currentToken == t_neg_ident)
	{
		attachNegativeChild(
			new BfIdentifier(tok.getValue().substr(1)) );
	}
	else if (currentToken == t_neg_paran)
	{
		attachNegativeChild(new BfExpression());
		moveToCurrentChild();
		moveToCurrentChild();
	}
	else if (currentToken == t_paran_end)
	{
		moveToParent();
	}
	else if (currentToken == t_holder_end)
	{
		moveToParent();
	}
	else if (currentToken == t_block_begin)
	{
		BfBlock * block = new BfBlock();

		scopeStack.back()->appendChild(nextScope);

		block->attachScope(nextScope);

		attachChildAsCurrent(block);
		scopeStack.push_back(nextScope);
		nextScope = new BfScopeNode();
	}
	else if (currentToken == t_block_end)
	{
		moveToParent();
		moveToParent();
		scopeStack.pop_back();
	}
	else if (currentToken == t_line_ending &&
		 ignoreNewlineStack.size() == 0 &&
		 lastToken != t_line_ending)
	{
                attachChild(new BfNewline());
	}
	else if (currentToken != t_line_ending)
	{
		cout << "Error: Unsupported token!" << endl;
		cout << "TokenId: " << currentToken << endl;
		exit(1);
	}

	lastToken = tok.getTokenValue();

	while (!current->canHoldMoreChildren())
	{
		moveToParent();
	}
}

void AstBuilder::attachChild(BfNode * n)
{
	current->appendChild(n);
}

void AstBuilder::attachChildAsCurrent(BfNode * n)
{
	attachChild(n);
	moveToCurrentChild();
}

void AstBuilder::moveToCurrentChild()
{
	current = current->currentChild();
}

void AstBuilder::moveToParent()
{
	current = current->getParent();
}

void AstBuilder::currentChildIsChildOf(BfNode * n)
{
	BfNode * ptr;
	ptr = current->popCurrentChild();
        n->appendChild(ptr);
        attachChild(n);
}

void AstBuilder::insertOperatorNode(BfBinaryOperator * n)
{
	while (current->numChildren() != 0 && n->higherPriorityThan(*(current->currentChild())))
	{
		moveToCurrentChild();
	}

	currentChildIsChildOf(n);
	moveToCurrentChild();
}

void AstBuilder::attachNegativeChild(BfNode * n)
{
	if (isOperator(current) || current->numChildren() == 0)
	{
		BfNegative * neg = new BfNegative();
                neg->appendChild(n);
                attachChild(neg);
	}
	else
	{
		insertOperatorNode(new BfMinus());
                attachChild(n);
	}
}

void AstBuilder::insertAssignmentNode(BfAssignment * n)
{
	BfExpression * exp = new BfExpression();
	currentChildrenAreChildrenOf(exp, t_line_ending);
	currentChildIsChildOf(n);
	moveToCurrentChild();
}

void AstBuilder::currentChildrenAreChildrenOf(BfNode * n, TokenName until)
{
	vector<BfNode *> temp;

	while (current->numChildren() != 0 && current->currentChild()->getTypeId() != until)
	{
		temp.push_back(current->popCurrentChild());
	}

	for (int i = temp.size()-1; i >= 0; i -= 1)
	{
		n->appendChild(temp[i]);
	}

	attachChild(n);
}
