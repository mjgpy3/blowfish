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

	root = blowfish;
	current = root;
	careAboutNewline = true;
}

BfNode * AstBuilder::buildAst(vector<FoundToken> tokens)
{
	for (int i = 0; i < tokens.size(); i += 1)
	{
		buildNode(tokens[i]);
	}

	return root;
}

void AstBuilder::buildNode(FoundToken tok)
{
	// TODO: PCFR: Rewrite me nicely (factories would be legit!)

	TokenName currentToken = tok.getTokenValue();

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
	else if (tokenImpliesScope(currentToken))
	{
		attachChildAsCurrent(
			BfBlockStarterNodeFactory(currentToken) );

                careAboutNewline = false;
	}
	else
	{

	switch (tok.getTokenValue())
	{
		case t_identifier:
		{
			attachChild(new BfIdentifier(tok.getValue()));
		} break;

		case t_neg_ident:
		{
			attachNegativeChild(new BfIdentifier(tok.getValue().substr(1)));
		} break;

		case t_kwd_self:
		{
			attachChild(new BfSelf());
		} break;

		case t_param_ident:
		{
			attachChild(new BfParameterIdentifier(tok.getValue()));
		} break;

		case t_kwd_forms:
		{
			attachChildAsCurrent(new BfFormsDef());
			careAboutNewline = false;
		} break;

		case t_kwd_not:
		{
			attachChildAsCurrent(new BfNot());
		} break;

		case t_kwd_require:
		{
			attachChildAsCurrent(new BfRequire());
		} break;

		case t_kwd_import:
		{
			attachChildAsCurrent(new BfImport());
		} break;

		case t_pipe:
		{
			attachChild(new BfPipe());
		} break;

		case t_kwd_return:
		{
			attachChild(new BfReturn());
		} break;

		case t_kwd_in:
		{
			attachChild(new BfIn());
		} break;

		case t_paran_begin:
		{
			attachChildAsCurrent(new BfExpression());
		} break;

		case t_neg_paran:
		{
			attachNegativeChild(new BfExpression());
			moveToCurrentChild();
			moveToCurrentChild();
		} break;

		case t_paran_end:
		{
			moveToParent();
			careAboutNewline = true;
		} break;

		case t_holder_begin:
		{
			attachChildAsCurrent(BfHolderFactory(tok.getValue().substr(0, 1)));
		} break;

		case t_holder_end:
		{
			moveToParent();
			careAboutNewline = true;
		} break;

		case t_block_begin:
		{
			attachChildAsCurrent(new BfBlock());
			careAboutNewline = true;
		} break;

		case t_block_end:
		{
			moveToParent();
			moveToParent();
		} break;

		case t_neg_integer:
		{
			attachNegativeChild(new BfInteger(tok.getValue().substr(1)));
		} break;

                case t_neg_float:
                {
                        attachNegativeChild(new BfFloat(tok.getValue().substr(1)));
                } break;

		case t_line_ending:
		{
			if (careAboutNewline &&
                            lastToken != t_line_ending && 
                            current->canHoldMoreChildren())
			{
				attachChild(new BfNewline());
			}
		} break;

		case t_op_dot:
		{
			attachChild(new BfDot());
		} break;

		default:
			cout << "Error: Unsupported token!" << endl;
			exit(1);
	}
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
	// PCFR: Nasty
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
