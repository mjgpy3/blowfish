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

#include "bfnodes.h"
#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;

BFNode::BFNode()
{
	infiniteCardinality = true;
        maxChildren = 0;
}

string BFNode::toString()
{
	string result = value + string(" -> [ ");

	for (int i = 0; i < children.size(); i += 1)
	{
		result += (*children[i]).toString() + string(", ");
	}

	return result + string(" ]"); 
}

void BFNode::setCardinality(int max)
{
	infiniteCardinality = false;
	maxChildren = max;
}

bool BFNode::canHoldMoreChildren()
{
	return infiniteCardinality || maxChildren < children.size();
}

BFNode::BFNode(string val)
{
	value = val;
}

void BFNode::appendChild(BFNode n)
{
	if (!canHoldMoreChildren())
	{
		cout << "Error: Tried to append a child to a full parent" << endl;
		exit(1);
	}
	n.parent = this;
	children.push_back(&n);
}

BFNode * BFNode::popCurrentChild()
{
	BFNode * ptr;
        ptr = children.back();
	children.pop_back();
	return ptr;
}
