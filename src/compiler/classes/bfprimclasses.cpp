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

#include "bfnumber.h"
#include "bfprimclasses.h"
#include "specialmethodnames.h"
using namespace std;

#ifndef BLOWFISH_PRIMITIVE_CLASS_DETAILS
#define BLOWFISH_PRIMITIVE_CLASS_DETAILS

// Blowfish string class
BfClass * STRING_CLASS = new BfClass( "String" );

void defineStringClass()
{
}

// Blowfish number class
BfClass * NUMBER_CLASS = new BfClass( "Number" );

BfObject * numericMathOperation( BfNumber * (*mathOp)(BfNumber*, BfNumber*), BfObject * op1, BfObject * op2 )
{
	BfObject * result = NUMBER_CLASS->getNewInstance();

        result->setNumericValue(
                mathOp(
			op1->getNumericValue(),
                     	op2->getNumericValue() ) );

        return result;
}

BfObject * numberClassAdd( BfParams * params )
{	
	return numericMathOperation( add, params->getParam( 0 ), params->getParam( 1 ) );
}
BfObject * numberClassSubtract( BfParams * params )
{
	return numericMathOperation( subtract, params->getParam( 0 ), params->getParam( 1 ) );
}
BfObject * numberClassMultiply( BfParams * params )
{
	return numericMathOperation( multiply, params->getParam( 0 ), params->getParam( 1 ) );
}
BfObject * numberClassDivide( BfParams * params )
{
	return numericMathOperation( divide, params->getParam( 0 ), params->getParam( 1 ) );
}
BfObject * numberClassModulus( BfParams * params )
{
	return numericMathOperation( mod, params->getParam( 0 ), params->getParam( 1 ) );
}
BfObject * numberClassPower( BfParams * params )
{
	return numericMathOperation( power, params->getParam( 0 ), params->getParam( 1 ) );
}
BfObject * numberClassNegate( BfParams * params )
{
	BfObject * result = NUMBER_CLASS->getNewInstance();
	
	result->setNumericValue( negateNum( params->getParam( 0 )->getNumericValue() ) );

	return result;
}
BfObject * numberClassShow( BfParams * params )
{
	BfObject * result = STRING_CLASS->getNewInstance();

	result->setStringValue( new BfStringValue( params->getParam(0)->getNumericValue()->toString() ) );

	return result;
}

void defineNumberClass()
{
	NUMBER_CLASS->addClassMethod( ADD_METH_NAME, new BfMethod( numberClassAdd ) );
	NUMBER_CLASS->addClassMethod( SUBTRACT_METH_NAME, new BfMethod( numberClassSubtract ) );
	NUMBER_CLASS->addClassMethod( MULTIPLY_METH_NAME, new BfMethod( numberClassMultiply ) );
	NUMBER_CLASS->addClassMethod( DIVIDE_METH_NAME, new BfMethod( numberClassDivide ) );
	NUMBER_CLASS->addClassMethod( MODULUS_METH_NAME, new BfMethod( numberClassModulus ) );
	NUMBER_CLASS->addClassMethod( POWER_METH_NAME, new BfMethod( numberClassPower ) );
	NUMBER_CLASS->addClassMethod( NEGATE_METH_NAME, new BfMethod( numberClassNegate ) );
	NUMBER_CLASS->addClassMethod( "show", new BfMethod( numberClassShow ) );
}

bool NUMBER_DEFINED = false;
bool STRING_DEFINED = false;

#endif

BfClass * getNumberClass()
{
	if (!NUMBER_DEFINED)
	{
		defineNumberClass();
		NUMBER_DEFINED = true;
	}
	return NUMBER_CLASS;
}

BfClass * getStringClass()
{
	if (!STRING_DEFINED)
	{
		defineStringClass();
		STRING_DEFINED = true;
	}
	return STRING_CLASS;
}
