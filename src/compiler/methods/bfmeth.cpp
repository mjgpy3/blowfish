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

#include <sstream>
#include "bfmeth.h"
#include "bftokennames.h"

string BfMethod::calculateSigniture( BfNode * node )
{
	string result = node->child(0)->getValue();
	int argNum = 1;

	for (int i = 1; i < node->numChildren(); i += 1)
	{
		if (node->child( i )->getTypeId() == t_block_begin)
		{
			return result;
		}
		stringstream ss;
		ss << argNum;
		result += getSignitureSeparator() + "a" + ss.str();
		argNum += 1;
	}

	// TODO: Error here
}
