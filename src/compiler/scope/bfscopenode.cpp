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
using namespace std;

BfScopeNode::BfScopeNode()
{
	name = "";
}

BfScopeNode::BfScopeNode(string scopeName)
{
	name = scopeName;
}

int BfScopeNode::numChildren()
{
	children.size();
}

void BfScopeNode::addIdentifierAndValue( string ident, BfNumber * value )
{
	identToNumber[ ident ] = value;
}

bool BfScopeNode::containsIdentifier( string ident )
{
	return true;
}

void BfScopeNode::appendChild(BfScopeNode * n)
{
	n->parent = this;
	children.push_back(n);
}

bool BfScopeNode::isNamed()
{
	return name != "";
}

void BfScopeNode::setName(string n)
{
	name = n;
}

string BfScopeNode::getName()
{
	return name;
}
