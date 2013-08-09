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

#include "bfnodefactory.h"
#include "bfnodes.h"
#include "bftokennames.h"
using namespace std;

BfBinaryOperator * BfOperatorNodeFactory(TokenName tok)
{
	if (tok == t_op_plus)
	{
		return new BfPlus();
	}
	if (tok == t_op_minus)
	{
		return new BfMinus();
	}
	if (tok == t_kwd_or)
	{
		return new BfOr();
	}
	if (tok == t_kwd_and)
	{
		return new BfAnd();
	}
	if (tok == t_op_gt)
	{
		return new BfGreaterThan();
	}
	if (tok == t_op_lt)
	{
		return new BfLessThan();
	}
	if (tok == t_op_geq)
	{
		return new BfGreaterThanOrEqual();
	}
	if (tok == t_op_leq)
	{
		return new BfLessThanOrEqual();
	}
	if (tok == t_op_eq)
	{
		return new BfEqual();
	}
	if (tok == t_op_noteq)
	{
		return new BfNotEqual();
	}
	if (tok == t_op_concat)
	{
		return new BfConcat();
	}
	if (tok == t_op_times)
	{
		return new BfMultiply();
	}
	if (tok == t_op_modulus)
	{
		return new BfModulus();
	}
	if (tok == t_op_divide)
	{
		return new BfDivide();
	}
	if (tok == t_op_pow)
	{
		return new BfPower();
	}
	if (tok == t_ellipsis)
	{
		return new BfEllipsis();
	}
}

