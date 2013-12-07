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
#include "bfparams.h"
#include "mitest.h"
using namespace std;

BfObject * aBfObject = new BfObject();

BfParams getParamsWithAnObject()
{
	BfParams params = BfParams();
	params.addParam( new BfObject() );
	return params;
}

void given_BfParams_when_a_param_is_added_to_the_collection_then_there_is_one_param(MiTester & tester)
{
	// Given
	BfParams params = BfParams();

	// When
	params.addParam( new BfObject() );

	// Then
	tester.assertTrue( 1 == params.count(), "When adding a param, then there is one param" );
}

void given_BfParams_when_a_param_is_added_to_the_collection_then_the_first_param_gotten_is_that_param(MiTester & tester)
{
	// Given
	BfParams params = BfParams();

	// When
	params.addParam( aBfObject );

	// Then
	tester.assertTrue( aBfObject == params.getParam( 0 ), "First param added can be gotten");
}

void given_BfParams_with_a_param_when_another_param_is_added_then_there_are_two(MiTester & tester)
{
	// Given
	BfParams params = getParamsWithAnObject();

	// When
	params.addParam( aBfObject );

	// Then
	tester.assertTrue( 2 == params.count(), "1+1=2 haha" );
}

int main()
{
	MiTester tester = MiTester();

	given_BfParams_when_a_param_is_added_to_the_collection_then_there_is_one_param( tester );
	given_BfParams_when_a_param_is_added_to_the_collection_then_the_first_param_gotten_is_that_param( tester );
	given_BfParams_with_a_param_when_another_param_is_added_then_there_are_two( tester );

	tester.printResults();
	return 0;
}
