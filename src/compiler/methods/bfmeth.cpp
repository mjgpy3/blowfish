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

#include "bfmeth.h"
#include "bftokennames.h"
#include "specialmethodnames.h"

BfMethod::BfMethod( BfNode * methodBody )
{
	body = methodBody;
	apiFunction = NULL;
	params = NULL;
}

BfMethod::BfMethod( BfObject * (*callable)(BfParams*) )
{
	apiFunction = callable;
	params = NULL;
}

string BfMethod::calculateSigniture( BfNode * node )
{
	string result = node->child(0)->getValue();

	for (int i = 1; i < node->numChildren(); i += 1)
	{
		TokenName currentType = node->child( i )->getTypeId();

		if (currentType == t_block_begin)
		{
			break;
		}
		else if (currentType == t_param_ident)
		{
			result += getSignitureSeparator() + node->child( i )->getValue();
		}
		else
		{
			result += getSignitureSeparator() + "a";
		}
	}

	return result;
}

BfMethod * BfMethod::provideParams( BfParams * someParams )
{
	params = someParams;
	return this;
}

bool BfMethod::hasParams()
{
	return params;
}

BfObject * BfMethod::call()
{
	if (apiFunction != NULL)
	{
		return apiFunction( params );
	}
	// TODO: Code here to execute a method body
}
