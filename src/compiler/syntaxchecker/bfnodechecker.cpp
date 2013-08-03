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
#include <vector>
using namespace std;

bool childrenAreExactly(BfNode * node, NodeIdentifier types[])
{
	int i;

	for (i = 0; i < (*node).numChildren(); i += 1)
	{
		if ((*(*node).child(i)).getTypeId() != types[i])
		{
			return false;
		}
	}
	
	return types[i] <= begin_identifiers ||
		types[i] >= end_identifiers;
}

bool isOperator(BfNode * node)
{
	return (*node).getTypeId() == id_or ||
	 	(*node).getTypeId() == id_and ||
		(*node).getTypeId() == id_plus ||
		(*node).getTypeId() == id_minus ||
		(*node).getTypeId() == id_power ||
		(*node).getTypeId() == id_multiply ||
		(*node).getTypeId() == id_divide ||
		(*node).getTypeId() == id_concat ||
		(*node).getTypeId() == id_modulus ||
		(*node).getTypeId() == id_gt ||
		(*node).getTypeId() == id_lt ||
		(*node).getTypeId() == id_geq ||
		(*node).getTypeId() == id_leq ||
		(*node).getTypeId() == id_neq ||
		(*node).getTypeId() == id_eq ||
		(*node).getTypeId() == id_ellipsis;

}

bool isLiteral(BfNode * node)
{
	return (*node).getTypeId() == id_string ||
		(*node).getTypeId() == id_integer ||
		(*node).getTypeId() == id_float;

}

bool impliesScope(BfNode * node)
{
	return (*node).getTypeId() == id_if ||
		(*node).getTypeId() == id_else_if ||
		(*node).getTypeId() == id_else ||
		(*node).getTypeId() == id_module ||
		(*node).getTypeId() == id_method ||
		(*node).getTypeId() == id_class || 
		(*node).getTypeId() == id_for || 
		(*node).getTypeId() == id_enum;
}

bool haveSameNodeStructure(BfNode * aNode, BfNode * anotherNode)
{
	if ((*aNode).numChildren() != (*anotherNode).numChildren())
	{
		return false;
	}
	if ((*aNode).getTypeId() != (*anotherNode).getTypeId())
	{
		return false;
	}
	if ((*aNode).numChildren() != 0)
	{
		for (int i = 0; i < (*aNode).numChildren(); i += 1)
		{
			if (!haveSameNodeStructure((*aNode).child(i), (*anotherNode).child(i)))
			{
				return false;
			}
		}
	}
	return true;
}

