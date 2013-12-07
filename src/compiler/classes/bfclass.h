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

#ifndef BLOWFISH_CLASSES
#define BLOWFISH_CLASSES

#include <map>
#include <string>
#include "bfmeth.h"
#include "bfnumber.h"
#include "bfparams.h"
#include "bfstring.h"
using namespace std;

class BfClass;
class BfMethod;

class BfObject
{
public:
        BfClass * getDefiningClass();
	void setDefiningClass( BfClass * defClass );

	BfNumber * getNumericValue();
	void setNumericValue( BfNumber * number );
	BfStringValue * getStringValue();
	void setStringValue( BfStringValue * aStringValue);

	string getTypeName();
	void setTypeName( string newTypeName );
private:
	BfClass * definingClass;
	BfNumber * numericValue;
	BfStringValue * stringValue;
	string typeName;
};

class BfClass
{
public:
	BfClass( string name );

	void addClassVariable( string ident, BfObject * variable );
	void addClassMethod( string methodSigniture, BfMethod * method );
	void isFormOf( BfClass * parent );

	bool containsVariable( string ident );
	bool containsMethod( string methodSigniture );

	string getTypeName();

	BfObject * getNewInstance();
	BfObject * callMethod( string methodName, BfParams * params );
	BfClass * provideSelf( BfObject * self );

private:
	map<string, BfObject*> variables;
	map<string, BfMethod*> methods;
	map<string, BfClass*> parents;

	string typeName;
	BfObject * selfObject;
};

#endif
