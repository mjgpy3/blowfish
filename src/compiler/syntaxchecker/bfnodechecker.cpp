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
	return node->getTypeId() == t_kwd_or ||
	 	node->getTypeId() == t_kwd_and ||
		node->getTypeId() == t_op_plus ||
		node->getTypeId() == t_op_minus ||
		node->getTypeId() == t_op_pow ||
		node->getTypeId() == t_op_times ||
		node->getTypeId() == t_op_divide ||
		node->getTypeId() == t_op_concat ||
		node->getTypeId() == t_op_modulus ||
		node->getTypeId() == t_op_gt ||
		node->getTypeId() == t_op_lt ||
		node->getTypeId() == t_op_geq ||
		node->getTypeId() == t_op_leq ||
		node->getTypeId() == t_op_noteq ||
		node->getTypeId() == t_op_eq ||
		node->getTypeId() == t_ellipsis;
}

bool isLiteral(BfNode * node)
{
	return node->getTypeId() == t_string ||
		node->getTypeId() == t_integer ||
		node->getTypeId() == t_float;

}

bool impliesScope(BfNode * node)
{
	return node->getTypeId() == t_kwd_if ||
		node->getTypeId() == t_kwd_elseif ||
		node->getTypeId() == t_kwd_else ||
		node->getTypeId() == t_kwd_module ||
		node->getTypeId() == t_kwd_meth ||
		node->getTypeId() == t_kwd_class || 
		node->getTypeId() == t_kwd_for || 
		node->getTypeId() == t_kwd_enum;
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

