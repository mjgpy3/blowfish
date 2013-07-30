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
#include "bfoperatorpriority.h"
#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;

BfNode::BfNode()
{
	infiniteCardinality = true;
        maxChildren = 0;
	priority = none;
	debugName = "BfNode";
}

string BfNode::toString()
{
	string result = debugName;

	if (children.size() != 0)
	{
		result += string(" -> [ ");
		for (int i = 0; i < children.size(); i += 1)
		{
			result += (*children[i]).toString() + string(", ");
		}

		return result + string("]"); 
	}
	return result;
}

bool BfNode::higherPriorityThan(BfNode n)
{
	if (n.priority == none || priority == none)
	{
		return false;
	}
	return priority > n.priority;
}

void BfNode::setCardinality(int max)
{
	infiniteCardinality = false;
	maxChildren = max;
}

bool BfNode::canHoldMoreChildren()
{
	return infiniteCardinality || maxChildren > children.size();
}

BfNode::BfNode(string val)
{
	value = val;
}

void BfNode::appendChild(BfNode * n)
{
	if (!canHoldMoreChildren())
	{
		cout << "Error: Tried to append a child to a full parent" << endl;
		exit(1);
	}
	(*n).parent = this;
	children.push_back(n);
}

BfHolder * BfHolderFactory(string spec)
{
        if (spec == "l")
        {
                return new BfList();
        }
        if (spec == "s")
        {
                return new BfSet();
        }
        if (spec == "d")
        {
                return new BfDictionary();
        }

        cout << "Error! Unrecognized factory specifier: " << spec << endl;
        exit(1);
}


BfNode * BfNode::popCurrentChild()
{
	BfNode * ptr;
        ptr = children.back();
	children.pop_back();
	return ptr;
}
