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

#ifndef BLOWFISH_SCOPE_NODE
#define BLOWFISH_SCOPE_NODE

#include <map>
#include <string>
#include <vector>
#include "bfclass.h"
using namespace std;

class BfObject;

class BfScopeNode
{
public:
	BfScopeNode();
	BfScopeNode(string scopeName);
	int numChildren();
	void appendChild(BfScopeNode * n);
	bool isNamed();
	void setName(string n);
	void addIdentifierAndValue( string ident, BfObject * value );
	string getName();
	BfScopeNode * getParent() { return parent; }
	bool containsIdentifier( string ident );

	BfObject * getObjectByIdentifier( string ident );

private:
	vector<BfScopeNode*> children;
	BfScopeNode * parent;
	string name;
	map<string, BfObject *> variables;
};

#endif
