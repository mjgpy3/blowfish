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

#ifndef BLOWFISH_SPECIAL_METHOD_NAMES
#define BLOWFISH_SPECIAL_METHOD_NAMES

#include <string>
using namespace std;

const string ADD_METH_NAME 				= "__add__";
const string SUBTRACT_METH_NAME 			= "__sub__";
const string MULTIPLY_METH_NAME 			= "__mul__";
const string DIVIDE_METH_NAME   			= "__div__";
const string MODULUS_METH_NAME  			= "__mod__";
const string POWER_METH_NAME    			= "__pow__";
const string NEGATE_METH_NAME  				= "__neg__";
const string CONCATINATE_METH_NAME 			= "__cat__";
const string IS_EQUAL_TO_METH_NAME			= "__eq__";
const string IS_LESS_THAN_METH_NAME			= "__lt__";
const string IS_GREATER_THAN_METH_NAME  		= "__gt__";
const string IS_GREATER_THAN_OR_EQUAL_TO_METH_NAME 	= "__geq__";
const string IS_LESS_THAN_OR_EQUAL_TO_METH_NAME		= "__leq__";
const string IS_NOT_EQUAL_TO_METH_NAME			= "__neq__";

#endif
