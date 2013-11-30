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

#include <iostream>
#include <string>
#include "bfclass.h"
#include "instancebuilder.h"
#include "mitest.h"
using namespace std;

void given_an_integer_in_string_form_when_an_Integer_instance_is_generated_from_it_then_that_instances_integer_value_is_the_integer_defined_in_the_string(MiTester & tester)
{
	// Given
	string number = "42";

	// When
	BfObject * result = (new InstanceBuilder)->buildInteger( number );

	// Then
	tester.assertTrue( 42 == result->getNumericValue()->getInt(), "When building an Integer, the resultant BfObject, has that numeric value");
}

void given_a_float_in_string_form_when_a_Float_instance_is_generated_from_it_then_that_instances_float_value_is_the_float_defined_in_the_string(MiTester & tester)
{
        // Given
        string number = "42.42";

        // When
        BfObject * result = (new InstanceBuilder)->buildFloat( number );

        // Then
        tester.assertTrue( 42.42 == result->getNumericValue()->getFloat(), "When building a Float, the resultant BfObject, has that numeric value");
}

void given_a_built_integer_when_its_defining_class_is_accessed_then_that_class_name_is_Number(MiTester & tester)
{
	// Given
	BfObject * integer = (new InstanceBuilder)->buildInteger( "42" );

	// When
	BfClass * definingClass = integer->getDefiningClass();

	// Then
	tester.assertEqual( definingClass->getTypeName(), "Number", "When instantiating an integer, its type name is Number" );
}

void given_a_built_float_when_its_defining_class_is_accessed_then_that_class_name_is_Number(MiTester & tester)
{
        // Given
        BfObject * floatingNumber = (new InstanceBuilder)->buildFloat( "42.42" );

        // When
        BfClass * definingClass = floatingNumber->getDefiningClass();

        // Then
        tester.assertEqual( definingClass->getTypeName(), "Number", "When instantiating an integer, its type name is Number" );
}

int main()
{
	MiTester tester = MiTester();

	given_an_integer_in_string_form_when_an_Integer_instance_is_generated_from_it_then_that_instances_integer_value_is_the_integer_defined_in_the_string(tester);
	given_a_float_in_string_form_when_a_Float_instance_is_generated_from_it_then_that_instances_float_value_is_the_float_defined_in_the_string(tester);
	given_a_built_integer_when_its_defining_class_is_accessed_then_that_class_name_is_Number(tester);
	given_a_built_float_when_its_defining_class_is_accessed_then_that_class_name_is_Number(tester);

	tester.printResults();
	return 0;
}
