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

#include "bfscopenode.h"
#include <vector>
using namespace std;

int BfScopeNode::numChildren()
{
	children.size();
}

void BfScopeNode::appendChild(BfScopeNode * n)
{
	(*n).parent = this;
	children.push_back(n);
}

bool BfScopeNode::parentIs(BfScopeNode * n)
{
	return (*this).parent == n;
}

void BfScopeNode::addIdentifer(BfNode * n)
{
	identifiers[(*n).getValue()] = new BfNode();
}

bool BfScopeNode::containsIdentifier(BfNode * n)
{
	return identifiers.count((*n).getValue()) == 1;
}

