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

#include "instancebuilder.h"

BfObject * InstanceBuilder::buildInteger( string numericValue )
{
	return getBfObjectWithNumber( new BfIntegerNumber( numericValue ) );
}

BfObject * InstanceBuilder::buildFloat( string numericValue )
{
	return getBfObjectWithNumber( new BfFloatNumber( numericValue ) );
}

BfObject * InstanceBuilder::getBfObjectWithNumber( BfNumber * number )
{
	BfObject * result = new BfObject();
        result->setNumericValue( number );
	// TODO: Create a namespace containing "primitive" classes
	result->setDefiningClass( new BfClass( "Number" ) );
        return result;
}
