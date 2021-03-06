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

#include "bfclass.h"

BfClass::BfClass( string name )
{
	typeName = name;
	selfObject = NULL;
}

void BfClass::addClassVariable( string ident, BfObject * variable )
{
	variables[ident] = variable;
}

void BfClass::addClassMethod( string methodSigniture, BfMethod * method )
{
	methods[methodSigniture] = method;
}

string BfClass::getTypeName()
{
	return typeName;
}

void BfClass::isFormOf( BfClass * parent )
{
	parents[parent->getTypeName()] = parent;
}

bool BfClass::containsVariable( string ident )
{
	return variables.find( ident ) != variables.end();
}

bool BfClass::containsMethod( string methodSigniture )
{
	return methods.find( methodSigniture) != methods.end();
}

BfObject * BfClass::getNewInstance()
{
	BfObject * anObject = new BfObject();

	anObject->setDefiningClass( this );

	return anObject;
}

BfObject * BfClass::callMethod( string methodName, BfParams * params )
{
	if (selfObject == NULL)
	{
		return methods[methodName]->provideParams(params)->call();
	}
	// TODO: Really consider whether this is what you want to do
	selfObject = NULL;

	return methods[methodName]->provideParams(params->selfAs( selfObject ))->call();
}

BfClass * BfClass::provideSelf( BfObject * self )
{
	selfObject = self;
	return this;
}
