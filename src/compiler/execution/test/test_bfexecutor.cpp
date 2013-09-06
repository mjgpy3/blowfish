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

void given_a_proper_ast_with_two_math_operations_when_we_execute_that_ast_the_result_is_stored(MiTester & tester)
{
	// Given
        BfExecutor executor = BfExecutor();

        BfRoot * root = new BfRoot();
        BfPlus * firstPlus = new BfPlus();
	BfPlus * secondPlus = new BfPlus();

	secondPlus->appendChild( new BfInteger( "7" ) );
	secondPlus->appendChild( new BfInteger( "21" ) );
	
	firstPlus->appendChild( new BfInteger("14") );
	firstPlus->appendChild( secondPlus );

	root->appendChild( firstPlus );

        // When
        executor.executeAst( root );

        // Then
        tester.assertTrue( 42 == executor.currentNumber->getInt(), "We can execute a simple AST with two addition operations under the root" );
}

void given_a_proper_ast_with_a_number_that_is_negated_when_we_execute_that_ast_the_result_is_stored(MiTester & tester)
{
	// Given
	BfExecutor executor = BfExecutor();

	BfRoot * root = new BfRoot();
	BfNegative * neg = new BfNegative();

	neg->appendChild( new BfInteger( "42" ) );
	root->appendChild( neg );

	// When
	executor.executeAst( root );
	
	// Then
	tester.assertTrue( -42 == executor.currentNumber->getInt(), "We can execute a simple AST with a negation" );
}

void given_a_proper_ast_with_an_operation_that_is_under_parans_when_we_execute_that_ast_the_results_is_stored(MiTester & tester)
{
	// Given
	BfExecutor executor = BfExecutor();

        BfRoot * root = new BfRoot();
	BfExpression * exp = new BfExpression();
	BfModulus * modu = new BfModulus();

	modu->appendChild( new BfInteger( "14" ) );
	modu->appendChild( new BfInteger( "5" ) );

	exp->appendChild( modu );

        root->appendChild( exp );

        // When
        executor.executeAst( root );

        // Then
        tester.assertTrue( 4 == executor.currentNumber->getInt(), "We can execute a simple AST with paranthesis" );
}

void given_an_ast_with_multiple_paranthesis_embedding_some_number_when_we_execute_that_ast_the_result_is_stored(MiTester & tester)
{
	// Given
        BfExecutor executor = BfExecutor();

        BfRoot * root = new BfRoot();
        BfExpression * exp1 = new BfExpression();
	BfExpression * exp2 = new BfExpression();
	BfExpression * exp3 = new BfExpression();
	BfExpression * exp4 = new BfExpression();

	exp4->appendChild( new BfInteger("42") );
	exp3->appendChild( exp4 );
	exp2->appendChild( exp3 );
	exp1->appendChild( exp2 );

        root->appendChild( exp1 );

        // When
        executor.executeAst( root );

        // Then
        tester.assertTrue( 42 == executor.currentNumber->getInt(), "We can execute a simple AST with many paranthesis" );
}

void assert_that_math_op_works_for( 
        BfInteger * firstNumber,
        BfInteger * secondNumber,
        BfBinaryOperator * op,
        long long expected,
        string opname,
        MiTester & tester )
{
        BfExecutor executor = BfExecutor();
        BfRoot * root = new BfRoot();
        
        op->appendChild( firstNumber );
        op->appendChild( secondNumber );

        root->appendChild( op );

        executor.executeAst( root );

        tester.assertTrue( expected == executor.currentNumber->getInt(), "The " + opname + " operator works" );
}

void all_math_operators_are_supported(MiTester & tester)
{
	BfInteger * aNumber = new BfInteger( "12" );
	BfInteger * anotherNumber = new BfInteger( "5" );

	assert_that_math_op_works_for( aNumber, anotherNumber, new BfPlus(), 17, "plus", tester );

	assert_that_math_op_works_for( aNumber, anotherNumber, new BfMinus(), 7, "minus", tester );

	assert_that_math_op_works_for( aNumber, anotherNumber, new BfMultiply(), 60, "multiply", tester );

	assert_that_math_op_works_for( aNumber, anotherNumber, new BfDivide(), 2, "divide", tester );

	assert_that_math_op_works_for( aNumber, anotherNumber, new BfModulus(), 2, "modulus", tester );

	assert_that_math_op_works_for( aNumber, anotherNumber, new BfPower(), 248832, "power", tester );
}

int main()
{
	MiTester tester = MiTester();

	given_an_ast_with_a_root_an_addition_operation_and_two_numerical_children_when_we_execute_that_ast_the_result_is_stored( tester );
	given_a_proper_ast_with_two_math_operations_when_we_execute_that_ast_the_result_is_stored( tester );
	given_a_proper_ast_with_a_number_that_is_negated_when_we_execute_that_ast_the_result_is_stored( tester );
	given_a_proper_ast_with_an_operation_that_is_under_parans_when_we_execute_that_ast_the_results_is_stored( tester );
	given_an_ast_with_multiple_paranthesis_embedding_some_number_when_we_execute_that_ast_the_result_is_stored( tester );

	all_math_operators_are_supported( tester );

	tester.printResults();
	return 0;
}
