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

#ifndef BLOWFISH_SEMANTIC_NODE
#define BLOWFISH_SEMANTIC_NODE

#include "bfnodes.h"
#include "bftokennames.h"
#include <vector>
using namespace std;

class SemanticNode
{
protected:
	BFNode * current;
};

class StartNode : protected SemanticNode
{
private:
	SemanticNode * next;
};

class EndNode : protected SemanticNode
{
public:
	void buildCurrentNode();
};

class OrNode : protected SemanticNode
{
private:
	vector<BFNode *> options;
	SemanticNode * next;
};

class DefNode : protected SemanticNode
{
private:
	SemanticNode * sub;
	SemanticNode * next;
};

class MatchNode : protected SemanticNode
{
private:
	TokenName matches;
	SemanticNode * next;
};

#endif
