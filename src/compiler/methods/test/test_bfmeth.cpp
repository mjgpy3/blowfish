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
#include "bfmeth.h"
#include "bfnodes.h"
#include "mitest.h"
using namespace std;

string separator = "$";

void given_a_BfMethodDef_with_an_identifier_and_a_block_as_its_children_when_we_generate_that_methods_signature_then_it_is_just_the_identifiers_value(MiTester & tester)
{
	// Given
	BfMethodDef * methodAst = new BfMethodDef();
	methodAst->appendChild( new BfIdentifier( "someIdentifier" ) );
	methodAst->appendChild( new BfBlock() );

	// When
	string result = BfMethod::calculateSigniture( methodAst );

	// Then
	tester.assertEqual( "someIdentifier", result, "When a methodDef has no params, then its signiture is just the method's identifier");
}

void given_a_BfMethodDef_with_an_identifier_a_single_parameter_and_a_block_when_we_generate_its_method_signiture_then_it_is_the_identifier_and_a_generic_string_with_some_separator( MiTester & tester)
{
        // Given
        BfMethodDef * methodAst = new BfMethodDef();
        methodAst->appendChild( new BfIdentifier( "someIdentifier" ) );
	methodAst->appendChild( new BfIdentifier( "someParam" ));
        methodAst->appendChild( new BfBlock() );

        // When
        string result = BfMethod::calculateSigniture( methodAst );

        // Then
        tester.assertEqual( "someIdentifier" + separator + "a1", result, "When a methodDef has a single param, then its signiture is ident$a1");
}

int main()
{
	MiTester tester = MiTester();

	given_a_BfMethodDef_with_an_identifier_and_a_block_as_its_children_when_we_generate_that_methods_signature_then_it_is_just_the_identifiers_value( tester );
	given_a_BfMethodDef_with_an_identifier_a_single_parameter_and_a_block_when_we_generate_its_method_signiture_then_it_is_the_identifier_and_a_generic_string_with_some_separator( tester );

	tester.printResults();
	return 0;
}
