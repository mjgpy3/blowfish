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

#ifndef BLOWFISH_METHOD
#define BLOWFISH_METHOD

#include <string>
#include "bfclass.h"
#include "bfnodes.h"
#include "bfparams.h"
using namespace std;

class BfNode;
class BfObject;
class BfParams;

class BfMethod
{
public:
	static string calculateSigniture( BfNode * node ); 
	static string getSignitureSeparator() { return "$"; }

	BfMethod( BfNode * methodBody );
	BfMethod( BfObject * (*callable)(BfParams*) );

	BfMethod * provideParams( BfParams * someParams );
	bool hasParams();

	BfObject * call();

private:
	BfNode * body;
	BfObject* (*apiFunction)(BfParams*);
	BfParams * params;
};


#endif
