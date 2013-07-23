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
#include <iostream>
#include <cstdlib>
#include "foundtoken.h"
#include "bfnodes.h"
using namespace std;

AstBuilder::AstBuilder()
{
	// The global namespace, BFRoot
	BFNode blowfish = BFRoot(); 

	root = &blowfish;
	current = root;
	numLevelsAfterNext = 0;
}

void AstBuilder::buildNode(FoundToken tok)
{
	// The switches that are met here are the ones that actually generate nodes
	switch (tok.getTokenValue())
	{
		case t_identifier:
		{
			attachChild(BFIdentifier(tok.getValue()));
		} break;
		case t_param_ident:
		{
			BFParamDef paramContainer = BFParamDef();
			paramContainer.appendChild(BFParamIdent(tok.getValue()));

			attachChild(paramContainer);
			moveToCurrentChild();
			numLevelsAfterNext = 1;
		} break;
		default:
			cout << "Error: Unsupported token!" << endl;
			exit(1);
	}

	while (numLevelsAfterNext > 0)
	{
		moveToParent();
		numLevelsAfterNext -= 1;
	}

}

void AstBuilder::attachChild(BFNode n)
{
	(*current).appendChild(n);
}

void AstBuilder::moveToCurrentChild()
{
	current = (*current).currentChild();
}

void AstBuilder::moveToParent()
{
	current = (*current).getParent();
}

void AstBuilder::lastChildIsChildOf(BFNode n)
{
	BFNode * ptr;
	ptr = (*current).popCurrentChild();
        n.appendChild(*ptr);
        attachChild(n);
	
}

int main()
{
	cout << "Hello Semantic Parser!" << endl;
	return 0;
}
