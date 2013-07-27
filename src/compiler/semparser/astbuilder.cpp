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
			attachChild(new BFClassDef());
		} break;

		case t_kwd_module:
		{
			attachChildAsCurrent(new BFModuleDef());
			careAboutNewline = false;
		} break;

		case t_kwd_meth:
		{
			attachChildAsCurrent(new BFMethodDef());
		} break;

		case t_kwd_not:
		{
			attachChildAsCurrent(new BFNot());
		} break;

		case t_paren_begin:
		{
			attachChildAsCurrent(new BFExpression());
		} break;

		case t_paren_end:
		{
			moveToParent();
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
		} break;

		case t_kwd_elseif:
		{
			attachChildAsCurrent(new BFElseIf());
		} break;

		case t_kwd_else:
		{
			attachChildAsCurrent(new BFElse());
		} break;

		case t_string:
		{
			attachChild(new BFString(tok.getValue()));
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

		// TODO: Implement rules for operator tokens

		default:
			cout << "Error: Unsupported token!" << endl;
			exit(1);
	}

	lastToken = tok.getTokenValue();

	cout << "Done handling token..." << endl;
	cout << "Cardinality of new node: " << (*current).maxChildren << endl;
	while (!(*current).canHoldMoreChildren())
	{
		moveToParent();
	}

	// cout << "Current TREE:\n    ";
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
	while ((*current).numChildren() != 0 && (*current).higherPriorityThan(*((*current).currentChild())))
	{
		moveToCurrentChild();
	}

	currentChildIsChildOf(n);
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
