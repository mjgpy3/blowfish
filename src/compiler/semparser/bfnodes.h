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

#include "bftokennames.h"
#include <vector>
#include <string>
using namespace std;

class BFNode
{
public:
	BFNode(string val);
	BFNode();
	void appendChild(BFNode n);
	BFNode * currentChild() { return children[indexLast()]; }
	BFNode * popCurrentChild();
        BFNode * getParent() { return parent; }
	bool canHoldMoreChildren();
	void setCardinality(int max);
	string toString();

private:
	vector<BFNode*> children;
	BFNode * parent;
	TokenName * type;
	int indexLast() { return children.size()-1; }
	string value;
	bool infiniteCardinality;
	int maxChildren;
};

class BFRoot : public BFNode
{
public:
	BFRoot() : BFNode() {}
};

class BFIdentifier : public BFNode
{
public:
	BFIdentifier(string value) : BFNode(value) { setCardinality(0); }
};

class BFParameterIdentifier : public BFNode
{
public:
	BFParameterIdentifier(string value) : BFNode(value) { }
};

class BFAssignment : public BFNode
{
public:
	BFAssignment() : BFNode() { setCardinality(2); }
};

class BFVariableAssignment : public BFAssignment
{
public:
	BFVariableAssignment() : BFAssignment() { }
};

class BFConstantAssignment : public BFAssignment
{
public:
	BFConstantAssignment() : BFAssignment() { }
};

class BFParameterlessDef : public BFNode
{
public:
	BFParameterlessDef() : BFNode() { setCardinality(2); }
};

class BFClassDef : public BFParameterlessDef
{
public:
	BFClassDef() : BFParameterlessDef() { }
};

class BFModuleDef : public BFParameterlessDef
{
public:
	BFModuleDef() : BFParameterlessDef() { }
};

class BFMethodDef : public BFNode
{
public:
	BFMethodDef() : BFNode() { }
};

class BFNot : public BFNode
{
public:
	BFNot() : BFNode() { setCardinality(1); }
};

class BFExpression : public BFNode
{
public:
	BFExpression() : BFNode() { }
};

class BFBlock : public BFNode
{
public:
	BFBlock() : BFNode() { }
};

class BFIf : public BFNode
{
public:
	BFIf() : BFNode() { }
};

class BFElseIf : public BFNode
{
public:
	BFElseIf() : BFNode() { }
};

class BFElse : public BFNode
{
public:
	// Else should only contain a block...
	BFElse() : BFNode() { setCardinality(1); }
};

#endif
