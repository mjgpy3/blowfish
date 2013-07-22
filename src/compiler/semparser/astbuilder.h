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
#include <vector>
using namespace std;

class AstBuilder
{
public:
	AstBuilder();
	BFNode buildAst(vector<FoundToken> tokens);
	void buildNode(FoundToken tok);

	void attachChild(BFNode n);
	void moveToCurrentChild();
	void moveToParent();
	void currentChildsParentIs(BFNode n);

private:
	BFNode * root;
	BFNode * current;
};

#endif
