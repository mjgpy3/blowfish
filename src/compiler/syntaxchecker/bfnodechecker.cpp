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

#include "bfnodechecker.h"
#include "bftokennames.h"
#include <vector>
using namespace std;

bool childrenAreExactly(BfNode * node, TokenName types[])
{
	int i;

	for (i = 0; i < node->numChildren(); i += 1)
	{
		if (node->child(i)->getTypeId() != types[i])
		{
			return false;
		}
	}
	
	return types[i] < (TokenName)0 ||
		types[i] >= end_tokens;
}

bool isOperator(BfNode * node)
{
	return isOperatorToken(node->getTypeId());
}

bool isOperatorToken(TokenName name)
{
	return name == t_kwd_or ||
                name == t_kwd_and ||
                name == t_op_plus ||
                name == t_op_minus ||
                name == t_op_pow ||
                name == t_op_times ||
                name == t_op_divide ||
                name == t_op_concat ||
                name == t_op_modulus ||
                name == t_op_gt ||
                name == t_op_lt ||
                name == t_op_geq ||
                name == t_op_leq ||
                name == t_op_noteq ||
                name == t_op_eq ||
                name == t_ellipsis;
}

bool isLiteral(BfNode * node)
{
	return isLiteralToken(node->getTypeId());
}

bool isLiteralToken(TokenName name)
{
	return name == t_string ||
                name == t_integer ||
                name == t_float;

}

bool isAssignment(BfNode * node)
{
	return isAssignmentToken(node->getTypeId());
}

bool isAssignmentToken(TokenName name)
{
	return name == t_kwd_is ||
		name == t_op_assign ||
		name == t_kwd_isnow;
}

bool impliesScope(BfNode * node)
{
	return tokenImpliesScope(node->getTypeId());
}

bool tokenImpliesScope(TokenName name)
{
	return name == t_kwd_if ||
                name == t_kwd_elseif ||
                name == t_kwd_else ||
                name == t_kwd_module ||
                name == t_kwd_meth ||
                name == t_kwd_class ||
                name == t_kwd_for ||
                name == t_kwd_enum;
}

bool haveSameNodeStructure(BfNode * aNode, BfNode * anotherNode)
{
	if (aNode->numChildren() != anotherNode->numChildren())
	{
		return false;
	}
	if (aNode->getTypeId() != anotherNode->getTypeId())
	{
		return false;
	}
	if (aNode->numChildren() != 0)
	{
		for (int i = 0; i < aNode->numChildren(); i += 1)
		{
			if (!haveSameNodeStructure(aNode->child(i), (*anotherNode).child(i)))
			{
				return false;
			}
		}
	}
	return true;
}

