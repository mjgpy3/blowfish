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

#ifndef BLOWFISH_AST_NODES
#define BLOWFISH_AST_NODES

#include <vector>
#include <string>
using namespace std;

class BFNode
{
public:
	BFNode(string value);
	BFNode();
private:
	vector<BFNode*> children;
	BFNode * parent;
	TokenName * type;
	int indexLast() { return children.size()-1; }
};

class BFRoot : private BFNode
{
};

class BFIdentifier : private BFNode
{
public:
	BFIdentifier(string value) : BFNode(value);
};

#endif
