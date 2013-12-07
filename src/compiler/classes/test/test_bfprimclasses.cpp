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

#include "bfprimclasses.h"
#include "specialmethodnames.h"
#include "mitest.h"
using namespace std;

void given_nothing_when_the_number_class_is_accessed_its_name_is_Number(MiTester & tester)
{
	// Given

	// When
	BfClass * numberClass = getNumberClass();

	// Then
	tester.assertEqual( "Number", numberClass->getTypeName(), "Number class has 'Number' name");
}

void assert_number_class_has_method( string methodName, MiTester & tester )
{
	// Given

        // When
        BfClass * numberClass = getNumberClass();

        // Then
        tester.assertTrue( numberClass->containsMethod( methodName ), "Numbers have " + methodName );
}

int main()
{
	MiTester tester = MiTester();

	given_nothing_when_the_number_class_is_accessed_its_name_is_Number( tester );
	assert_number_class_has_method( ADD_METH_NAME, tester );
	assert_number_class_has_method( SUBTRACT_METH_NAME, tester );
	assert_number_class_has_method( MULTIPLY_METH_NAME, tester );
	assert_number_class_has_method( DIVIDE_METH_NAME, tester );
	assert_number_class_has_method( MODULUS_METH_NAME, tester );
	assert_number_class_has_method( POWER_METH_NAME, tester );
	assert_number_class_has_method( NEGATE_METH_NAME, tester );

	tester.printResults();
	return 0;
}
