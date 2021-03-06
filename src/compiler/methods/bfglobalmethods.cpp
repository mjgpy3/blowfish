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

#include "bfglobalmethods.h"
#include <iostream>

BfObject * sayMethod( BfParams * params )
{
	if (params->count() == 0)
	{
		cout << endl;
	}
	else
	{
		BfObject * current = params->getParam( 0 );
		// TODO: Keep show method name somewhere else
		cout << current->getDefiningClass()->provideSelf(current)->callMethod("show", new BfParams());
	}
	// TODO: Return NONE object instead of this placeholder
	return new BfObject();
}
