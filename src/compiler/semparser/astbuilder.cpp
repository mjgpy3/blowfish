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

#include "astbuilder.h"
#include "bflexer.h"
#include <iostream>
#include <typeinfo>
#include <cstdlib>
#include "foundtoken.h"
#include "bfnodes.h"
using namespace std;

AstBuilder::AstBuilder()
{
	// The global namespace, BFRoot
	BFNode * blowfish = new BFRoot(); 

	root = blowfish;
	current = root;
	careAboutNewline = true;
}

BFNode * AstBuilder::buildAst(vector<FoundToken> tokens)
{
	for (int i = 0; i < tokens.size(); i += 1)
	{
		buildNode(tokens[i]);
	}

	return root;
}

void AstBuilder::buildNode(FoundToken tok)
{
	// TODO: Add "Don't care about newline until you see an open bracket" logic
	cout << "Processing: " << tok.getTokenValue() << endl;
	cout << "Current node's number of children: " << (*current).numChildren() << endl;
	// The switches that are met here are the ones that actually generate nodes

	switch (tok.getTokenValue())
	{
		case t_identifier:
		{
			attachChild(new BFIdentifier(tok.getValue()));
		} break;

		case t_neg_ident:
		{
			attachNegativeChild(new BFIdentifier(tok.getValue().substr(1)));
		} break;

		case t_param_ident:
		{
			attachChild(new BFParameterIdentifier(tok.getValue()));
		} break;

		case t_kwd_isnow:
		{
			currentChildIsChildOf(new BFVariableAssignment());
			moveToCurrentChild();
		} break;

		case t_op_assign:
		{
			currentChildIsChildOf(new BFVariableAssignment());
                        moveToCurrentChild();
		} break;

		case t_kwd_is:
		{
			currentChildIsChildOf(new BFConstantAssignment());
			moveToCurrentChild();
		} break;

		case t_kwd_class:
		{
			attachChildAsCurrent(new BFClassDef());
			careAboutNewline = false;
		} break;

		case t_kwd_module:
		{
			attachChildAsCurrent(new BFModuleDef());
			careAboutNewline = false;
		} break;

		case t_kwd_meth:
		{
			attachChildAsCurrent(new BFMethodDef());
			careAboutNewline = false;
		} break;

		case t_kwd_forms:
		{
			attachChildAsCurrent(new BFFormsDef());
			careAboutNewline = false;
		} break;

		case t_kwd_not:
		{
			attachChildAsCurrent(new BFNot());
		} break;

		case t_pipe:
		{
			attachChild(new BFPipe());
		} break;

		case t_kwd_in:
		{
			attachChild(new BFIn());
		} break;

		case t_paran_begin:
		{
			attachChildAsCurrent(new BFExpression());
		} break;

		case t_neg_paran:
		{
			attachNegativeChild(new BFExpression());
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
			attachChildAsCurrent(BFHolderFactory(tok.getValue().substr(0, 1)));
		} break;

		case t_holder_end:
		{
			moveToParent();
			careAboutNewline = true;
		} break;

		case t_block_begin:
		{
			attachChildAsCurrent(new BFBlock());
			careAboutNewline = true;
		} break;

		case t_block_end:
		{
			moveToParent();
			moveToParent();
		} break;

		case t_kwd_if:
		{
			attachChildAsCurrent(new BFIf());
			careAboutNewline = false;
		} break;

		case t_kwd_elseif:
		{
			attachChildAsCurrent(new BFElseIf());
			careAboutNewline = false;
		} break;

		case t_kwd_else:
		{
			attachChildAsCurrent(new BFElse());
			careAboutNewline = false;
		} break;

		case t_string:
		{
			attachChild(new BFString(tok.getValue()));
		} break;

		case t_integer:
		{
			attachChild(new BFInteger(tok.getValue()));
		} break;

		case t_neg_integer:
		{
			attachNegativeChild(new BFInteger(tok.getValue().substr(1)));
		} break;

		case t_float:
		{
			attachChild(new BFFloat(tok.getValue()));
		} break;

                case t_neg_float:
                {
                        attachNegativeChild(new BFFloat(tok.getValue().substr(1)));
                } break;

		case t_line_ending:
		{
			if (careAboutNewline &&
                            lastToken != t_line_ending && 
                            (*current).canHoldMoreChildren())
			{
				attachChild(new BFNewline());
			}
		} break;

		case t_kwd_or:
		{
			insertOperatorNode(new BFOr());
		} break;

		case t_kwd_and:
		{
			insertOperatorNode(new BFAnd());
		} break;

		case t_op_eq:
		{
			insertOperatorNode(new BFEqual());
		} break;

		case t_op_noteq:
		{
			insertOperatorNode(new BFNotEqual());
		} break;

		case t_op_lt:
		{
			insertOperatorNode(new BFLessThan());
		} break;

		case t_op_gt:
		{
			insertOperatorNode(new BFGreaterThan());
		} break;

		case t_op_geq:
		{
			insertOperatorNode(new BFGreaterThanOrEqual());
		} break;

		case t_op_leq:
		{
			insertOperatorNode(new BFLessThanOrEqual());
		} break;

		// TODO: Store above as (nodes to not), apply not in parent method

		case t_op_plus:
		{
			insertOperatorNode(new BFPlus());
		} break;

		case t_op_minus:
		{
			insertOperatorNode(new BFMinus());
		} break;

		case t_op_concat:
		{
			insertOperatorNode(new BFConcat());
		} break;

		case t_op_times:
		{
			insertOperatorNode(new BFMultiply());
		} break;

		case t_op_divide:
		{
			insertOperatorNode(new BFDivide());
		} break;

		case t_op_modulus:
		{
			insertOperatorNode(new BFModulus());
		} break;

		case t_op_pow:
		{
			insertOperatorNode(new BFPower());
		} break;

		case t_ellipsis:
		{
			insertOperatorNode(new BFEllipsis());
		} break;

		default:
			cout << "Error: Unsupported token!" << endl;
			exit(1);
	}

	lastToken = tok.getTokenValue();

	while (!(*current).canHoldMoreChildren())
	{
		moveToParent();
	}
}

void AstBuilder::attachChild(BFNode * n)
{
	(*current).appendChild(n);
	cout << "Attached Child\n";
}

void AstBuilder::attachChildAsCurrent(BFNode * n)
{
	attachChild(n);
	moveToCurrentChild();
}

void AstBuilder::moveToCurrentChild()
{
	current = (*current).currentChild();
	cout << "Moved to current child\n";
}

void AstBuilder::moveToParent()
{
	cout << "Trying to move to parent" << endl;
	current = (*current).getParent();
	cout << "Moved to parent\n";
}

void AstBuilder::currentChildIsChildOf(BFNode * n)
{
	BFNode * ptr;
	ptr = (*current).popCurrentChild();
        (*n).appendChild(ptr);
        attachChild(n);
}

void AstBuilder::insertOperatorNode(BFBinaryOperator * n)
{
	while ((*current).numChildren() != 0 && (*n).higherPriorityThan(*((*current).currentChild())))
	{
		moveToCurrentChild();
	}

	currentChildIsChildOf(n);
	moveToCurrentChild();
}

void AstBuilder::attachNegativeChild(BFNode * n)
{
        BFNegative * neg = new BFNegative();
        (*neg).appendChild(n);
	attachChild(neg);
}

int main()
{
	cout << "Hello Semantic Parser!" << endl;

	BFNode * ast;

	BfLexer lexer = BfLexer();
	AstBuilder builder = AstBuilder();
	lexer.parseTokensFromFile("hello_world.bf");

	ast = builder.buildAst(lexer.getTokens());

	cout << (*ast).toString() << endl;

	return 0;
}
