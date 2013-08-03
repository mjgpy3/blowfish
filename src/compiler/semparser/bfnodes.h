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

enum NodeIdentifier
{
	begin_identifiers = 424,
	id_naked_node,
	id_blowfish_root,
	id_identifier,
	id_parameter_identifier,
	id_variable_assignment,
	id_constant_assignment,
	id_forms,
	id_pipe,
	id_dot,
	id_in,
	id_class,
	id_module,
	id_method,
	id_for,
	id_enum,
	id_require,
	id_import,
	id_not,
	id_expression,
	id_block,
	id_if,
	id_else_if,
	id_else,
	id_or,
	id_and,
	id_plus,
	id_minus,
	id_power,
	id_multiply,
	id_divide,
	id_concat,
	id_modulus,
	id_newline,
	id_gt,
	id_lt,
	id_geq,
	id_leq,
	id_neq,
	id_eq,
	id_ellipsis,
	id_negative,
	id_set,
	id_list,
	id_dictionary,
	id_string,
	id_integer,
	id_float,
	end_identifiers,
};

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
	BfNode * child(int i) { return children[i]; }
	int numChildren() { return children.size(); }
	bool canHoldMoreChildren();
	void setCardinality(int max);
	bool higherPriorityThan(BfNode n);
	string toString();
	OperatorPriority priority;
	string debugName;
	int maxChildren;
	NodeIdentifier getTypeId() { return nodeIdent; }
	void setTypeId(NodeIdentifier id) { nodeIdent = id; }

private:
	vector<BfNode*> children;
	BfNode * parent;
	TokenName * type;
	int indexLast() { return children.size()-1; }
	string value;
	bool infiniteCardinality;
	NodeIdentifier nodeIdent;	

};

//!
//! The global root of all of the blowfish AST
//!
class BfRoot : public BfNode
{
public:
	BfRoot() : BfNode() 
	{ 
		debugName = "Blowfish Root";
		setTypeId(id_blowfish_root);
	}
};

//!
//! An identifier, the AST doesn't care if it's a method call, a variable or your Auntie's casarole recipe... Later things will care
//!
class BfIdentifier : public BfNode
{
public:
	BfIdentifier(string value) : BfNode(value)
	{
		setCardinality(0);
		debugName = string("Ident:") + value;
		setTypeId(id_identifier);
	}
};

//!
//!
//!
class BfParameterIdentifier : public BfNode
{
public:
	BfParameterIdentifier(string value) : BfNode(value)
	{
		debugName = string("ParaIdent:") + value;
		setTypeId(id_parameter_identifier);
	}
};

//!
//! The base of the real assignment classes
//!
class BfAssignment : public BfNode
{
public:
	BfAssignment() : BfNode() 
	{
		setCardinality(2);
		priority = absoluteLowest;
	}
};

//!
//! A variable assignment... See any other language
//!
class BfVariableAssignment : public BfAssignment
{
public:
	BfVariableAssignment() : BfAssignment() 
	{
		debugName = "VarAssignment";
		setTypeId(id_variable_assignment);
	}
};

//!
//! A constant assignment
//!
class BfConstantAssignment : public BfAssignment
{
public:
	BfConstantAssignment() : BfAssignment()
	{
		debugName = "ConstAssignemnt";
		setTypeId(id_constant_assignment);
	}
};

//!
//! The base class for nodes that are definitions of something (e.g. class) that don't take parameters
//!
class BfParameterlessDef : public BfNode
{
public:
	BfParameterlessDef() : BfNode() 
	{
		setCardinality(2);
	}
};

class BfFormsDef : public BfParameterlessDef
{
public:
	BfFormsDef() : BfParameterlessDef()
	{
		debugName = "Forms";
		setTypeId(id_forms);
	}
};

class BfPipe : public BfNode
{
public:
	BfPipe() : BfNode() 
	{
		setCardinality(0);
		debugName = "|";
		setTypeId(id_pipe);
	}
};

class BfDot : public BfNode
{
public:
	BfDot() : BfNode() 
	{
		setCardinality(0);
		debugName = ".";
		setTypeId(id_dot);
	}
};

class BfIn : public BfNode
{
public:
	BfIn() : BfNode() 
	{
		setCardinality(0);
		debugName = "In";
		setTypeId(id_in);
	}
};

//!
//! A class definition
//!
class BfClassDef : public BfParameterlessDef
{
public:
	BfClassDef() : BfParameterlessDef()
	{
		debugName = "Class";
		setTypeId(id_class);
	}
};

//!
//! A module definition
//!
class BfModuleDef : public BfParameterlessDef
{
public:
	BfModuleDef() : BfParameterlessDef()
	{
		debugName = "Module";
		setTypeId(id_module);
	}
};

//!
//! A method definition
//!
class BfMethodDef : public BfNode
{
public:
	BfMethodDef() : BfNode()
	{
		debugName = "Method";
		setTypeId(id_method);
	}
};

class BfForLoop : public BfNode
{
public:
	BfForLoop() : BfNode()
	{
		debugName = "For";
		setTypeId(id_for);
	}
};

class BfEnumLoop : public BfNode
{
public:
	BfEnumLoop() : BfNode()
	{
		debugName = "Enum";
		setTypeId(id_enum);
	}
};

class BfRequire : public BfNode
{
public:
	BfRequire() : BfNode() 
	{
		setCardinality(1);
		debugName = "Require";
		setTypeId(id_require);
	}
};

class BfImport : public BfNode
{
public:
	BfImport() : BfNode() 
	{
		setCardinality(1);
		debugName = "Import";
		setTypeId(id_import);
	}
};

//!
//! A negation operation, only takes one subnode
//!
class BfNot : public BfNode
{
public:
	BfNot() : BfNode() 
	{
		setCardinality(1);
		debugName = "Not";
		setTypeId(id_not);
	}
};

//!
//! Some expression, kind of a container for parenthesized (sp) expressions
//!
class BfExpression : public BfNode
{
public:
	BfExpression() : BfNode()
	{
		debugName = "(...)";
		setTypeId(id_expression);
	}
};

//!
//! Some block of code, you know, like in a definition
//!
class BfBlock : public BfNode
{
public:
	BfBlock() : BfNode()
	{
		debugName = "[...]";
		setTypeId(id_block);
	}
};

//!
//! An if statement
//!
class BfIf : public BfNode
{
public:
	BfIf() : BfNode()
	{
		debugName = "if";
		setTypeId(id_if);
	}
};

//!
//! An if else statement
//!
class BfElseIf : public BfNode
{
public:
	BfElseIf() : BfNode()
	{
		debugName = "else if";
		setTypeId(id_else_if);
	}
};

//!
//! An else statement, should only have 1 child (being a block)
//!
class BfElse : public BfNode
{
public:
	// Else should only contain a block...
	BfElse() : BfNode() 
	{
		setCardinality(1);
		debugName = "else";
		setTypeId(id_else);
	}
};

//!
//! A newline...  This is really a way to separate statements
//!
class BfNewline : public BfNode
{
public:
	BfNewline() : BfNode() 
	{
		setCardinality(0);
		debugName = "nl";
		setTypeId(id_newline);
	}
};

class BfBinaryOperator : public BfNode
{
public:
	BfBinaryOperator(OperatorPriority p) : BfNode() 
	{
		priority = p;
		setCardinality(2);
	}

};

class BfOr : public BfBinaryOperator
{
public:
	BfOr() : BfBinaryOperator(lowest)
	{
		debugName = "OR";
		setTypeId(id_or);
	}

};

class BfAnd : public BfBinaryOperator
{
public:
	BfAnd() : BfBinaryOperator(lowest)
	{
		debugName = "AND";
		setTypeId(id_and);
	}
};

class BfGreaterThan : public BfBinaryOperator
{
public:
	BfGreaterThan() : BfBinaryOperator(low)
	{
		debugName = ">";
		setTypeId(id_gt);
	}
};

class BfLessThan : public BfBinaryOperator
{
public:
	BfLessThan() : BfBinaryOperator(low)
	{
		debugName = "<";
		setTypeId(id_lt);
	}
};

class BfGreaterThanOrEqual : public BfBinaryOperator
{
public:
	BfGreaterThanOrEqual() : BfBinaryOperator(low)
	{
		debugName = ">=";
		setTypeId(id_geq);
	}
};

class BfLessThanOrEqual : public BfBinaryOperator
{
public:
        BfLessThanOrEqual() : BfBinaryOperator(low)
	{
		debugName = "<=";
		setTypeId(id_leq);
	}
};

class BfEqual : public BfBinaryOperator
{
public:
	BfEqual() : BfBinaryOperator(low)
	{
		debugName = "=";
		setTypeId(id_eq);
	}
};

class BfNotEqual : public BfBinaryOperator
{
public:
	BfNotEqual() : BfBinaryOperator(low)
	{
		debugName = "/=";
		setTypeId(id_neq);
	}
};

class BfPlus : public BfBinaryOperator
{
public:
	BfPlus() : BfBinaryOperator(medium)
	{
		debugName = "+";
		setTypeId(id_plus);
	}
};

class BfMinus : public BfBinaryOperator
{
public:
	BfMinus() : BfBinaryOperator(medium)
	{
		debugName = "-";
		setTypeId(id_minus);
	}
};

class BfConcat : public BfBinaryOperator
{
public:
	BfConcat() : BfBinaryOperator(medium)
	{
		debugName = "++";
		setTypeId(id_concat);
	}
};

class BfMultiply : public BfBinaryOperator
{
public:
	BfMultiply() : BfBinaryOperator(high)
	{
		debugName = "*";
		setTypeId(id_multiply);}
};

class BfDivide : public BfBinaryOperator
{
public:
	BfDivide() : BfBinaryOperator(high)
	{
		debugName = "/";
		setTypeId(id_divide);
	}
};

class BfModulus : public BfBinaryOperator
{
public:
	BfModulus() : BfBinaryOperator(high)
	{
		debugName = "%";
		setTypeId(id_modulus);
	}
};

class BfPower : public BfBinaryOperator
{
public:
	BfPower() : BfBinaryOperator(highest)
	{
		debugName = "^";
		setTypeId(id_power);
	}
};

class BfEllipsis : public BfBinaryOperator
{
public:
	BfEllipsis() : BfBinaryOperator(highest)
	{
		debugName = "..";
		setTypeId(id_ellipsis);
	}
};

class BfLiteral : public BfNode
{
public:
	BfLiteral(string value) : BfNode(value) 
	{
		setCardinality(0);
		debugName = value;
	}
};

class BfString : public BfLiteral
{
public:
	BfString(string value) : BfLiteral(value) 
	{
		setTypeId(id_string);
	}
};

class BfInteger : public BfLiteral
{
public:
	BfInteger(string value) : BfLiteral(value) 
	{
		setTypeId(id_integer);
	}
};

class BfFloat : public BfLiteral
{
public:
	BfFloat(string value) : BfLiteral(value) 
	{
		setTypeId(id_float);
	}
};

class BfNegative : public BfNode
{
public:
	BfNegative() : BfNode()
	{
		debugName = "-";
		setCardinality(1);
		setTypeId(id_negative);
	}
};

class BfHolder : public BfNode
{
public:
	BfHolder() : BfNode() { }
};

class BfList : public BfHolder
{
public:
	BfList() : BfHolder()
	{
		debugName = "l{...}";
		setTypeId(id_list);
	}
};

class BfSet : public BfHolder
{
public:
	BfSet() : BfHolder()
	{
		debugName = "s{...}";
		setTypeId(id_set);
	}
};

class BfDictionary : public BfHolder
{
public:
	BfDictionary() : BfHolder()
	{
		debugName = "d{...}";
		setTypeId(id_dictionary);
	}
};

BfHolder * BfHolderFactory(string spec);

#endif
