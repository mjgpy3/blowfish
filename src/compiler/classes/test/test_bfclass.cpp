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

#include <string>
#include "bfclass.h"
#include "mitest.h"
using namespace std;

void given_bfclass_when_we_initialize_it_then_its_type_name_is_the_value_we_pass_through_the_constructor( MiTester & tester )
{
	// Given, When
	BfClass * someClass = new BfClass( "aClass" );

	// Then
	tester.assertEqual( someClass->getTypeName(), "aClass", "A class' name must be given upon construction" );
}

void given_a_BfClass_when_we_add_a_new_BfObject_to_it_then_that_BfClass_contains_that_BfObject_as_identifiable_by_a_string( MiTester & tester )
{
	// Given
	BfClass * someClass = new BfClass( "Something" );

	// When
	someClass->addClassVariable( "classVar", new BfObject() );

	// Then
	tester.assertTrue( someClass->containsVariable( "classVar" ), "When we add a variable to a class then we can see that it exists in that class" );
}

void given_a_BfClass_when_we_add_a_new_class_variable_to_it_then_a_different_identifier_will_not_specify_that_variable( MiTester & tester )
{
	// Given
	BfClass * someClass = new BfClass( "Something" );

	// When
	someClass->addClassVariable( "someVar", new BfObject() );

	// Then
	tester.assertFalse( someClass->containsVariable( "anotherVar" ), "A class does not contain a variable whose identifier is not added");
}

void given_a_BfClass_when_we_add_a_new_method_to_it_then_we_it_can_be_seen_that_it_is_contained( MiTester & tester )
{
	// Given
	BfClass * someClass = new BfClass( "Something" );

	// When
	someClass->addClassMethod( "method$id:$a", new BfMethod( new BfBlock() ) );

	// Then
	tester.assertTrue( someClass->containsMethod( "method$id:$a" ), "When a method is added we can see that it exists in a class" );
}

void given_a_BfClass_when_we_add_a_new_method_to_it_then_that_method_is_only_accessible_through_its_very_signiture( MiTester & tester )
{
	// Given
	BfClass * someClass = new BfClass( "sdfg" );

	// When
	someClass->addClassMethod( "someMethod", new BfMethod( new BfBlock() ) );

	// Then
	tester.assertFalse( someClass->containsMethod( "anotherMethod" ), "A class does not contain a method whose signiture is not added" );
}

void given_a_BfClass_when_we_get_a_new_instance_of_that_class_then_the_instances_defining_class_is_that_BfClass( MiTester & tester )
{
	// Given
	BfClass * someClass = new BfClass( "aClassYo" );

	// When
	BfObject * instance = someClass->getNewInstance();

	// Then
	tester.assertTrue( instance->getDefiningClass() == someClass, "When we get an instance of a class, that instance's defining class is the class from which we got the instance" );
}

void given_a_BfObject_when_we_set_its_numeric_value_then_that_same_value_can_be_retrieved( MiTester & tester )
{
	// Given
	BfObject * anObject = new BfObject();
	BfIntegerNumber * number = new BfIntegerNumber( "42" );

	// When
	anObject->setNumericValue( number );

	// Then
	tester.assertTrue( number == anObject->getNumericValue(),  "Sets and gets work for an object's numeric value");
}

int main()
{
	MiTester tester = MiTester();

	given_bfclass_when_we_initialize_it_then_its_type_name_is_the_value_we_pass_through_the_constructor( tester );
	given_a_BfClass_when_we_add_a_new_BfObject_to_it_then_that_BfClass_contains_that_BfObject_as_identifiable_by_a_string( tester );
	given_a_BfClass_when_we_add_a_new_class_variable_to_it_then_a_different_identifier_will_not_specify_that_variable( tester );
	given_a_BfClass_when_we_add_a_new_method_to_it_then_we_it_can_be_seen_that_it_is_contained( tester );
	given_a_BfClass_when_we_add_a_new_method_to_it_then_that_method_is_only_accessible_through_its_very_signiture( tester );
	given_a_BfClass_when_we_get_a_new_instance_of_that_class_then_the_instances_defining_class_is_that_BfClass( tester );
	given_a_BfObject_when_we_set_its_numeric_value_then_that_same_value_can_be_retrieved( tester );

	tester.printResults();
	return 0;
}
