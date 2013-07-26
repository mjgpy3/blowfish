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
#include "bfoperatorpriority.h"
#include <vector>
#include <string>
using namespace std;

//!
//! The base class for all Blowfish nodes in the AST
//!
class BFNode
{
public:
	BFNode(string val);
	BFNode();
	void appendChild(BFNode * n);
	BFNode * currentChild() { return children.back(); }
	BFNode * popCurrentChild();
        BFNode * getParent() { return parent; }
	int numChildren() { return children.size(); }
	bool canHoldMoreChildren();
	void setCardinality(int max);
	bool higherPriorityThan(BFNode n);
	string toString();
	OperatorPriority priority;
	string debugName;
	int maxChildren;

private:
	vector<BFNode*> children;
	BFNode * parent;
	TokenName * type;
	int indexLast() { return children.size()-1; }
	string value;
	bool infiniteCardinality;
};

//!
//! The global root of all of the blowfish AST
//!
class BFRoot : public BFNode
{
public:
	BFRoot() : BFNode() { debugName = "Blowfish Root"; }
};

//!
//! An identifier, the AST doesn't care if it's a method call, a variable or your Auntie's casarole recipe... Later things will care
//!
class BFIdentifier : public BFNode
{
public:
	BFIdentifier(string value) : BFNode(value) { setCardinality(0); debugName = string("Ident:") + value; }
};

//!
//!
//!
class BFParameterIdentifier : public BFNode
{
public:
	BFParameterIdentifier(string value) : BFNode(value) { debugName = string("ParaIdent:") + value; }
};

//!
//! The base of the real assignment classes
//!
class BFAssignment : public BFNode
{
public:
	BFAssignment() : BFNode() { setCardinality(2); }
};

//!
//! A variable assignment... See any other language
//!
class BFVariableAssignment : public BFAssignment
{
public:
	BFVariableAssignment() : BFAssignment() { debugName = "VarAssignment"; }
};

//!
//! A constant assignment
//!
class BFConstantAssignment : public BFAssignment
{
public:
	BFConstantAssignment() : BFAssignment() { debugName = "ConstAssignemnt"; }
};

//!
//! The base class for nodes that are definitions of something (e.g. class) that don't take parameters
//!
class BFParameterlessDef : public BFNode
{
public:
	BFParameterlessDef() : BFNode() { setCardinality(2); }
};

//!
//! A class definition
//!
class BFClassDef : public BFParameterlessDef
{
public:
	BFClassDef() : BFParameterlessDef() { debugName = "Class"; }
};

//!
//! A module definition
//!
class BFModuleDef : public BFParameterlessDef
{
public:
	BFModuleDef() : BFParameterlessDef() { debugName = "Module"; }
};

//!
//! A method definition
//!
class BFMethodDef : public BFNode
{
public:
	BFMethodDef() : BFNode() { debugName = "Method"; }
};

//!
//! A negation operation, only takes one subnode
//!
class BFNot : public BFNode
{
public:
	BFNot() : BFNode() { setCardinality(1); debugName = "Not"; }
};

//!
//! Some expression, kind of a container for parenthesized (sp) expressions
//!
class BFExpression : public BFNode
{
public:
	BFExpression() : BFNode() { debugName = "(...)"; }
};

//!
//! Some block of code, you know, like in a definition
//!
class BFBlock : public BFNode
{
public:
	BFBlock() : BFNode() { debugName = "[...]"; }
};

//!
//! An if statement
//!
class BFIf : public BFNode
{
public:
	BFIf() : BFNode() { debugName = "if"; }
};

//!
//! An if else statement
//!
class BFElseIf : public BFNode
{
public:
	BFElseIf() : BFNode() { debugName = "else if"; }
};

//!
//! An else statement, should only have 1 child (being a block)
//!
class BFElse : public BFNode
{
public:
	// Else should only contain a block...
	BFElse() : BFNode() { setCardinality(1); debugName = "else"; }
};

//!
//! A newline...  This is really a way to separate statements
//!
class BFNewline : public BFNode
{
public:
	BFNewline() : BFNode() { setCardinality(0); debugName = "nl"; }
};

// TODO: Implement operators

class BFBinaryOperator : public BFNode
{
public:
	BFBinaryOperator(OperatorPriority p) : BFNode() { priority = p; setCardinality(2); }
	OperatorPriority getPriority() { return priority; }

};

class BFPlus : public BFBinaryOperator
{
public:
	BFPlus() : BFBinaryOperator(medium) { }
};

class BFMinus : public BFBinaryOperator
{
public:
	BFMinus() : BFBinaryOperator(medium) { }
};

class BFLiteral : public BFNode
{
public:
	BFLiteral(string value) : BFNode(value) { setCardinality(0); debugName = value;  }
};

class BFString : public BFLiteral
{
public:
	BFString(string value) : BFLiteral(value) { }
};

#endif
