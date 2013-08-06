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
#include "bfnodechecker.h"
#include <iostream>
#include <typeinfo>
#include <cstdlib>
#include "foundtoken.h"
#include "bfnodes.h"
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

		case t_kwd_isnow:
		{
			//currentChildIsChildOf(new BfVariableAssignment());
			//moveToCurrentChild();
			insertAssignmentNode(new BfVariableAssignment());
		} break;

		case t_op_assign:
		{
			//currentChildIsChildOf(new BfVariableAssignment());
                        //moveToCurrentChild();
			insertAssignmentNode(new BfVariableAssignment());
		} break;

		case t_kwd_is:
		{
			//currentChildIsChildOf(new BfConstantAssignment());
			//moveToCurrentChild();
			insertAssignmentNode(new BfConstantAssignment());
		} break;

		case t_kwd_class:
		{
			attachChildAsCurrent(new BfClassDef());
			careAboutNewline = false;
		} break;

		case t_kwd_module:
		{
			attachChildAsCurrent(new BfModuleDef());
			careAboutNewline = false;
		} break;

		case t_kwd_meth:
		{
			attachChildAsCurrent(new BfMethodDef());
			careAboutNewline = false;
		} break;

		case t_kwd_for:
		{
			attachChildAsCurrent(new BfForLoop());
			careAboutNewline = false;
		} break;

		case t_kwd_enum:
		{
			attachChildAsCurrent(new BfEnumLoop());
			careAboutNewline = false;
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

		case t_kwd_if:
		{
			attachChildAsCurrent(new BfIf());
			careAboutNewline = false;
		} break;

		case t_kwd_elseif:
		{
			attachChildAsCurrent(new BfElseIf());
			careAboutNewline = false;
		} break;

		case t_kwd_else:
		{
			attachChildAsCurrent(new BfElse());
			careAboutNewline = false;
		} break;

		case t_string:
		{
			attachChild(new BfString(tok.getValue()));
		} break;

		case t_integer:
		{
			attachChild(new BfInteger(tok.getValue()));
		} break;

		case t_neg_integer:
		{
			attachNegativeChild(new BfInteger(tok.getValue().substr(1)));
		} break;

		case t_float:
		{
			attachChild(new BfFloat(tok.getValue()));
		} break;

		case t_char:
		{
			attachChild(new BfString(tok.getValue()));
		} break;

                case t_neg_float:
                {
                        attachNegativeChild(new BfFloat(tok.getValue().substr(1)));
                } break;

		case t_line_ending:
		{
			if (careAboutNewline &&
                            lastToken != t_line_ending && 
                            (*current).canHoldMoreChildren())
			{
				attachChild(new BfNewline());
			}
		} break;

		case t_kwd_or:
		{
			insertOperatorNode(new BfOr());
		} break;

		case t_kwd_and:
		{
			insertOperatorNode(new BfAnd());
		} break;

		case t_op_dot:
		{
			attachChild(new BfDot());
		} break;

		case t_op_eq:
		{
			insertOperatorNode(new BfEqual());
		} break;

		case t_op_noteq:
		{
			insertOperatorNode(new BfNotEqual());
		} break;

		case t_op_lt:
		{
			insertOperatorNode(new BfLessThan());
		} break;

		case t_op_gt:
		{
			insertOperatorNode(new BfGreaterThan());
		} break;

		case t_op_geq:
		{
			insertOperatorNode(new BfGreaterThanOrEqual());
		} break;

		case t_op_leq:
		{
			insertOperatorNode(new BfLessThanOrEqual());
		} break;

		case t_op_plus:
		{
			insertOperatorNode(new BfPlus());
		} break;

		case t_op_minus:
		{
			insertOperatorNode(new BfMinus());
		} break;

		case t_op_concat:
		{
			insertOperatorNode(new BfConcat());
		} break;

		case t_op_times:
		{
			insertOperatorNode(new BfMultiply());
		} break;

		case t_op_divide:
		{
			insertOperatorNode(new BfDivide());
		} break;

		case t_op_modulus:
		{
			insertOperatorNode(new BfModulus());
		} break;

		case t_op_pow:
		{
			insertOperatorNode(new BfPower());
		} break;

		case t_ellipsis:
		{
			insertOperatorNode(new BfEllipsis());
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

void AstBuilder::attachChild(BfNode * n)
{
	(*current).appendChild(n);
}

void AstBuilder::attachChildAsCurrent(BfNode * n)
{
	attachChild(n);
	moveToCurrentChild();
}

void AstBuilder::moveToCurrentChild()
{
	current = (*current).currentChild();
}

void AstBuilder::moveToParent()
{
	current = (*current).getParent();
}

void AstBuilder::currentChildIsChildOf(BfNode * n)
{
	BfNode * ptr;
	ptr = (*current).popCurrentChild();
        (*n).appendChild(ptr);
        attachChild(n);
}

void AstBuilder::insertOperatorNode(BfBinaryOperator * n)
{
	while ((*current).numChildren() != 0 && (*n).higherPriorityThan(*((*current).currentChild())))
	{
		moveToCurrentChild();
	}

	currentChildIsChildOf(n);
	moveToCurrentChild();
}

void AstBuilder::attachNegativeChild(BfNode * n)
{
	if (isOperator(current) || (*current).numChildren() == 0)
	{
		BfNegative * neg = new BfNegative();
                (*neg).appendChild(n);
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
	currentChildrenAreChildrenOf(exp, id_newline);
	currentChildIsChildOf(n);
	moveToCurrentChild();
}

void AstBuilder::currentChildrenAreChildrenOf(BfNode * n, NodeIdentifier until)
{
	// PCFR: Nasty
	vector<BfNode *> temp;

	while ((*current).numChildren() != 0 && (*((*current).currentChild())).getTypeId() != until)
	{
		temp.push_back((*current).popCurrentChild());
		cout << (*current).numChildren() << endl;
	}

	for (int i = temp.size()-1; i >= 0; i -= 1)
	{
		(*n).appendChild(temp[i]);
	}

	attachChild(n);
}
