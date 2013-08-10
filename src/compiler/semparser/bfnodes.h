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
#include "bfscopenode.h"
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
	BfNode * child(int i) { return children[i]; }
	int numChildren() { return children.size(); }
	bool canHoldMoreChildren();
	void setCardinality(int max);
	void attachScope(BfScopeNode * scopeNode);
	BfScopeNode * getScope();
	bool higherPriorityThan(BfNode n);
	string toString();
	string debugName;
	string getValue() { return value; }
	OperatorPriority priority;
	TokenName getTypeId() { return nodeIdent; }
	void setTypeId(TokenName id) { nodeIdent = id; }

private:
	vector<BfNode*> children;
	BfNode * parent;
	BfScopeNode * scope;
	int indexLast() { return children.size()-1; }
	int maxChildren;
	string value;
	bool infiniteCardinality;
	TokenName nodeIdent;

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
		setTypeId(t_root);
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
		setTypeId(t_identifier);
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
		setTypeId(t_param_ident);
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
		setTypeId(t_op_assign);
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
		setTypeId(t_kwd_is);
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
		setTypeId(t_kwd_forms);
	}
};

class BfPipe : public BfNode
{
public:
	BfPipe() : BfNode() 
	{
		setCardinality(0);
		debugName = "|";
		setTypeId(t_pipe);
	}
};

class BfDot : public BfNode
{
public:
	BfDot() : BfNode() 
	{
		setCardinality(0);
		debugName = ".";
		setTypeId(t_op_dot);
	}
};

class BfIn : public BfNode
{
public:
	BfIn() : BfNode() 
	{
		setCardinality(0);
		debugName = "In";
		setTypeId(t_kwd_in);
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
		setTypeId(t_kwd_class);
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
		setTypeId(t_kwd_module);
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
		setTypeId(t_kwd_meth);
	}
};

class BfLambda : public BfNode
{
public:
	BfLambda() : BfNode()
	{
		debugName = "\\";
		setTypeId(t_kwd_lambda);
	}
};

class BfForLoop : public BfNode
{
public:
	BfForLoop() : BfNode()
	{
		debugName = "For";
		setTypeId(t_kwd_for);
	}
};

class BfEnumLoop : public BfNode
{
public:
	BfEnumLoop() : BfNode()
	{
		debugName = "Enum";
		setTypeId(t_kwd_enum);
	}
};

class BfRequire : public BfNode
{
public:
	BfRequire() : BfNode() 
	{
		setCardinality(1);
		debugName = "Require";
		setTypeId(t_kwd_require);
	}
};

class BfImport : public BfNode
{
public:
	BfImport() : BfNode() 
	{
		setCardinality(1);
		debugName = "Import";
		setTypeId(t_kwd_import);
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
		setTypeId(t_kwd_not);
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
		setTypeId(t_paran_begin);
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
		setTypeId(t_block_begin);
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
		setTypeId(t_kwd_if);
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
		setTypeId(t_kwd_elseif);
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
		setTypeId(t_kwd_else);
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
		setTypeId(t_line_ending);
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
		setTypeId(t_kwd_or);
	}

};

class BfAnd : public BfBinaryOperator
{
public:
	BfAnd() : BfBinaryOperator(lowest)
	{
		debugName = "AND";
		setTypeId(t_kwd_and);
	}
};

class BfGreaterThan : public BfBinaryOperator
{
public:
	BfGreaterThan() : BfBinaryOperator(low)
	{
		debugName = ">";
		setTypeId(t_op_gt);
	}
};

class BfLessThan : public BfBinaryOperator
{
public:
	BfLessThan() : BfBinaryOperator(low)
	{
		debugName = "<";
		setTypeId(t_op_lt);
	}
};

class BfGreaterThanOrEqual : public BfBinaryOperator
{
public:
	BfGreaterThanOrEqual() : BfBinaryOperator(low)
	{
		debugName = ">=";
		setTypeId(t_op_geq);
	}
};

class BfLessThanOrEqual : public BfBinaryOperator
{
public:
        BfLessThanOrEqual() : BfBinaryOperator(low)
	{
		debugName = "<=";
		setTypeId(t_op_leq);
	}
};

class BfEqual : public BfBinaryOperator
{
public:
	BfEqual() : BfBinaryOperator(low)
	{
		debugName = "=";
		setTypeId(t_op_eq);
	}
};

class BfNotEqual : public BfBinaryOperator
{
public:
	BfNotEqual() : BfBinaryOperator(low)
	{
		debugName = "/=";
		setTypeId(t_op_noteq);
	}
};

class BfPlus : public BfBinaryOperator
{
public:
	BfPlus() : BfBinaryOperator(medium)
	{
		debugName = "+";
		setTypeId(t_op_plus);
	}
};

class BfMinus : public BfBinaryOperator
{
public:
	BfMinus() : BfBinaryOperator(medium)
	{
		debugName = "-";
		setTypeId(t_op_minus);
	}
};

class BfConcat : public BfBinaryOperator
{
public:
	BfConcat() : BfBinaryOperator(medium)
	{
		debugName = "++";
		setTypeId(t_op_concat);
	}
};

class BfMultiply : public BfBinaryOperator
{
public:
	BfMultiply() : BfBinaryOperator(high)
	{
		debugName = "*";
		setTypeId(t_op_times);}
};

class BfDivide : public BfBinaryOperator
{
public:
	BfDivide() : BfBinaryOperator(high)
	{
		debugName = "/";
		setTypeId(t_op_divide);
	}
};

class BfModulus : public BfBinaryOperator
{
public:
	BfModulus() : BfBinaryOperator(high)
	{
		debugName = "%";
		setTypeId(t_op_modulus);
	}
};

class BfPower : public BfBinaryOperator
{
public:
	BfPower() : BfBinaryOperator(highest)
	{
		debugName = "^";
		setTypeId(t_op_pow);
	}
};

class BfEllipsis : public BfBinaryOperator
{
public:
	BfEllipsis() : BfBinaryOperator(highest)
	{
		debugName = "..";
		setTypeId(t_ellipsis);
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
		setTypeId(t_string);
	}
};

class BfInteger : public BfLiteral
{
public:
	BfInteger(string value) : BfLiteral(value) 
	{
		setTypeId(t_integer);
	}
};

class BfFloat : public BfLiteral
{
public:
	BfFloat(string value) : BfLiteral(value) 
	{
		setTypeId(t_float);
	}
};

class BfNegative : public BfNode
{
public:
	BfNegative() : BfNode()
	{
		debugName = "-";
		setCardinality(1);
		setTypeId(t_neg);
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
		setTypeId(t_list);
	}
};

class BfSet : public BfHolder
{
public:
	BfSet() : BfHolder()
	{
		debugName = "s{...}";
		setTypeId(t_set);
	}
};

class BfSelf : public BfNode
{
public:
	BfSelf() : BfNode()
	{
		setCardinality(0);
		debugName = "Self";
		setTypeId(t_kwd_self);
	}
};

class BfDictionary : public BfHolder
{
public:
	BfDictionary() : BfHolder()
	{
		debugName = "d{...}";
		setTypeId(t_dict);
	}
};

class BfReturn : public BfNode
{
public:
	BfReturn() : BfNode()
	{
		debugName = "Return";
		setTypeId(t_kwd_return);
		setCardinality(0);
	}
};

BfHolder * BfHolderFactory(string spec);

#endif
