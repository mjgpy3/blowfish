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
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

//!
//! The base class for all Blowfish nodes in the AST
//!
class BfNode
{
public:
	BfNode(string val);
	BfNode();
	void appendChild(BfNode * n);
	BfNode * currentChild() { return children.back(); }
	BfNode * popCurrentChild();
        BfNode * getParent() { return parent; }
	int numChildren() { return children.size(); }
	bool canHoldMoreChildren();
	void setCardinality(int max);
	bool higherPriorityThan(BfNode n);
	string toString();
	OperatorPriority priority;
	string debugName;
	int maxChildren;

private:
	vector<BfNode*> children;
	BfNode * parent;
	TokenName * type;
	int indexLast() { return children.size()-1; }
	string value;
	bool infiniteCardinality;
};

//!
//! The global root of all of the blowfish AST
//!
class BfRoot : public BfNode
{
public:
	BfRoot() : BfNode() { debugName = "Blowfish Root"; }
};

//!
//! An identifier, the AST doesn't care if it's a method call, a variable or your Auntie's casarole recipe... Later things will care
//!
class BfIdentifier : public BfNode
{
public:
	BfIdentifier(string value) : BfNode(value) { setCardinality(0); debugName = string("Ident:") + value; }
};

//!
//!
//!
class BfParameterIdentifier : public BfNode
{
public:
	BfParameterIdentifier(string value) : BfNode(value) { debugName = string("ParaIdent:") + value; }
};

//!
//! The base of the real assignment classes
//!
class BfAssignment : public BfNode
{
public:
	BfAssignment() : BfNode() { setCardinality(2); priority = absoluteLowest; }
};

//!
//! A variable assignment... See any other language
//!
class BfVariableAssignment : public BfAssignment
{
public:
	BfVariableAssignment() : BfAssignment() { debugName = "VarAssignment"; }
};

//!
//! A constant assignment
//!
class BfConstantAssignment : public BfAssignment
{
public:
	BfConstantAssignment() : BfAssignment() { debugName = "ConstAssignemnt"; }
};

//!
//! The base class for nodes that are definitions of something (e.g. class) that don't take parameters
//!
class BfParameterlessDef : public BfNode
{
public:
	BfParameterlessDef() : BfNode() { setCardinality(2); }
};

class BfFormsDef : public BfParameterlessDef
{
public:
	BfFormsDef() : BfParameterlessDef() { debugName = "Forms"; }
};

class BfPipe : public BfNode
{
public:
	BfPipe() : BfNode() { setCardinality(0); debugName = "|"; }
};

class BfDot : public BfNode
{
public:
	BfDot() : BfNode() { setCardinality(0); debugName = "."; }
};

class BfIn : public BfNode
{
public:
	BfIn() : BfNode() { setCardinality(0); debugName = "In"; }
};

//!
//! A class definition
//!
class BfClassDef : public BfParameterlessDef
{
public:
	BfClassDef() : BfParameterlessDef() { debugName = "Class"; }
};

//!
//! A module definition
//!
class BfModuleDef : public BfParameterlessDef
{
public:
	BfModuleDef() : BfParameterlessDef() { debugName = "Module"; }
};

//!
//! A method definition
//!
class BfMethodDef : public BfNode
{
public:
	BfMethodDef() : BfNode() { debugName = "Method"; }
};

class BfForLoop : public BfNode
{
public:
	BfForLoop() : BfNode() { debugName = "For"; }
};

class BfEnumLoop : public BfNode
{
public:
	BfEnumLoop() : BfNode() { debugName = "Enum"; }
};

class BfRequire : public BfNode
{
public:
	BfRequire() : BfNode() { setCardinality(1); debugName = "Require"; }
};

class BfImport : public BfNode
{
public:
	BfImport() : BfNode() { setCardinality(1); debugName = "Import"; }
};

//!
//! A negation operation, only takes one subnode
//!
class BfNot : public BfNode
{
public:
	BfNot() : BfNode() { setCardinality(1); debugName = "Not"; }
};

//!
//! Some expression, kind of a container for parenthesized (sp) expressions
//!
class BfExpression : public BfNode
{
public:
	BfExpression() : BfNode() { debugName = "(...)"; }
};

//!
//! Some block of code, you know, like in a definition
//!
class BfBlock : public BfNode
{
public:
	BfBlock() : BfNode() { debugName = "[...]"; }
};

//!
//! An if statement
//!
class BfIf : public BfNode
{
public:
	BfIf() : BfNode() { debugName = "if"; }
};

//!
//! An if else statement
//!
class BfElseIf : public BfNode
{
public:
	BfElseIf() : BfNode() { debugName = "else if"; }
};

//!
//! An else statement, should only have 1 child (being a block)
//!
class BfElse : public BfNode
{
public:
	// Else should only contain a block...
	BfElse() : BfNode() { setCardinality(1); debugName = "else"; }
};

//!
//! A newline...  This is really a way to separate statements
//!
class BfNewline : public BfNode
{
public:
	BfNewline() : BfNode() { setCardinality(0); debugName = "nl"; }
};

class BfBinaryOperator : public BfNode
{
public:
	BfBinaryOperator(OperatorPriority p) : BfNode() { priority = p; setCardinality(2); }

};

class BfOr : public BfBinaryOperator
{
public:
	BfOr() : BfBinaryOperator(lowest) { debugName = "OR"; }
};

class BfAnd : public BfBinaryOperator
{
public:
	BfAnd() : BfBinaryOperator(lowest) { debugName = "AND"; }
};

class BfGreaterThan : public BfBinaryOperator
{
public:
	BfGreaterThan() : BfBinaryOperator(low) { debugName = ">"; }
};

class BfLessThan : public BfBinaryOperator
{
public:
	BfLessThan() : BfBinaryOperator(low) { debugName = "<"; }
};

class BfGreaterThanOrEqual : public BfBinaryOperator
{
public:
	BfGreaterThanOrEqual() : BfBinaryOperator(low) { debugName = ">="; }
};

class BfLessThanOrEqual : public BfBinaryOperator
{
public:
        BfLessThanOrEqual() : BfBinaryOperator(low) { debugName = "<="; }
};

class BfEqual : public BfBinaryOperator
{
public:
	BfEqual() : BfBinaryOperator(low) { debugName = "="; }
};

class BfNotEqual : public BfBinaryOperator
{
public:
	BfNotEqual() : BfBinaryOperator(low) { debugName = "/="; }
};

class BfPlus : public BfBinaryOperator
{
public:
	BfPlus() : BfBinaryOperator(medium) { debugName = "+"; }
};

class BfMinus : public BfBinaryOperator
{
public:
	BfMinus() : BfBinaryOperator(medium) { debugName = "-"; }
};

class BfConcat : public BfBinaryOperator
{
public:
	BfConcat() : BfBinaryOperator(medium) { debugName = "++"; }
};

class BfMultiply : public BfBinaryOperator
{
public:
	BfMultiply() : BfBinaryOperator(high) { debugName = "*";}
};

class BfDivide : public BfBinaryOperator
{
public:
	BfDivide() : BfBinaryOperator(high) { debugName = "/"; }
};

class BfModulus : public BfBinaryOperator
{
public:
	BfModulus() : BfBinaryOperator(high) { debugName = "%"; }
};

class BfPower : public BfBinaryOperator
{
public:
	BfPower() : BfBinaryOperator(highest) { debugName = "^"; }
};

class BfEllipsis : public BfBinaryOperator
{
public:
	BfEllipsis() : BfBinaryOperator(highest) { debugName = ".."; }
};

class BfLiteral : public BfNode
{
public:
	BfLiteral(string value) : BfNode(value) { setCardinality(0); debugName = value;  }
};

class BfString : public BfLiteral
{
public:
	BfString(string value) : BfLiteral(value) { }
};

class BfInteger : public BfLiteral
{
public:
	BfInteger(string value) : BfLiteral(value) { }
};

class BfFloat : public BfLiteral
{
public:
	BfFloat(string value) : BfLiteral(value) { }
};

class BfNegative : public BfNode
{
public:
	BfNegative() : BfNode() { debugName = "-"; setCardinality(1); }
};

class BfHolder : public BfNode
{
public:
	BfHolder() : BfNode() { }
};

class BfList : public BfHolder
{
public:
	BfList() : BfHolder() { debugName = "l{...}"; }
};

class BfSet : public BfHolder
{
public:
	BfSet() : BfHolder() { debugName = "s{...}"; }
};

class BfDictionary : public BfHolder
{
public:
	BfDictionary() : BfHolder() { debugName = "d{...}"; }
};

BfHolder * BfHolderFactory(string spec);

#endif
