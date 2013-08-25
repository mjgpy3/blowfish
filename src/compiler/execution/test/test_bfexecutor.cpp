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

#include "bfexecutor.h"
#include "bfnodes.h"
#include "mitest.h"
using namespace std;

void given_an_ast_with_a_root_an_addition_operation_and_two_numerical_children_when_we_execute_that_ast_the_result_is_stored(MiTester & tester)
{
	// Given
	BfExecutor executor = BfExecutor();

	BfRoot * root = new BfRoot();
        BfPlus * plus = new BfPlus();
        BfInteger * left = new BfInteger( "42" );
	BfInteger * right = new BfInteger( "24" );

	plus->appendChild( left );
	plus->appendChild( right );
	root->appendChild( plus );

	// When
	executor.executeAst( root );

	// Then
	tester.assertTrue( 66 == executor.currentNumber->getInt(), "We can execute a simple AST with just an addition operation under the root" );
}

int main()
{
	MiTester tester = MiTester();

	given_an_ast_with_a_root_an_addition_operation_and_two_numerical_children_when_we_execute_that_ast_the_result_is_stored(tester);

	tester.printResults();
	return 0;
}