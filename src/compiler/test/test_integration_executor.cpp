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

#include <fstream>
#include <string>
#include "mitest.h"
#include "bflexer.h"
#include "astbuilder.h"
#include "bfexecutor.h"
#include "bfnodes.h"
#include "bfnodechecker.h"
using namespace std;

string temp_file_name = "test_file.bf";

void write_temp_bf_file(string text)
{
	ofstream fout;

	remove(temp_file_name.c_str());

	fout.open(temp_file_name.c_str());
	fout << text;
	fout.close();
}

void given_some_code_with_just_a_number_when_it_is_run_then_the_stored_number_is_that_number(MiTester & tester)
{
	// Given
	string code = "42\n";
	BfLexer lexer = BfLexer();
	AstBuilder builder = AstBuilder();
	BfExecutor executor = BfExecutor();

	write_temp_bf_file( code );

	// When
	lexer.parseTokensFromFile( temp_file_name );
	BfNode * ast = builder.buildAst( lexer.getTokens() );
	executor.executeAst( ast );

	// Then
	tester.assertTrue( 42 == executor.currentNumber->getInt(), "When a blowfish file with just a number is executed, the executor picks up on it" );
}

void given_some_code_with_just_a_math_operation_when_it_is_run_then_the_stored_number_is_that_number(MiTester & tester)
{
        // Given
        string code = "98 - 56\n";
        BfLexer lexer = BfLexer();
        AstBuilder builder = AstBuilder();
        BfExecutor executor = BfExecutor();

        write_temp_bf_file( code );

        // When
        lexer.parseTokensFromFile( temp_file_name );
        BfNode * ast = builder.buildAst( lexer.getTokens() );
        executor.executeAst( ast );

        // Then
        tester.assertTrue( 42 == executor.currentNumber->getInt(), "When a blowfish file with just a math operation is executed, the executor picks up on it" );
}

void given_a_math_expression_with_a_negative_when_we_execute_it_then_the_expected_result_is_found(MiTester & tester)
{
	// Given
        string code = "98 - -56\n";
        BfLexer lexer = BfLexer();
        AstBuilder builder = AstBuilder();
        BfExecutor executor = BfExecutor();

        write_temp_bf_file( code );

        // When
        lexer.parseTokensFromFile( temp_file_name );
        BfNode * ast = builder.buildAst( lexer.getTokens() );
        executor.executeAst( ast );

        // Then
        tester.assertTrue( 154 == executor.currentNumber->getInt(), "Operations with negatives work" );
}

void given_a_complex_math_expression_when_we_execute_it_then_the_result_is_what_we_would_expect1(MiTester & tester)
{
	// Given
        string code = "((2^6 - -4 + 7) * -1)\n";
        BfLexer lexer = BfLexer();
        AstBuilder builder = AstBuilder();
        BfExecutor executor = BfExecutor();

        write_temp_bf_file( code );

        // When
        lexer.parseTokensFromFile( temp_file_name );
        BfNode * ast = builder.buildAst( lexer.getTokens() );
        executor.executeAst( ast );

        // Then
        tester.assertTrue( -75 == executor.currentNumber->getInt(), "-75 == ((2^6 - -4 + 7) * -1)" );
}

void given_a_complex_math_expression_when_we_execute_it_then_the_result_is_what_we_would_expect2(MiTester & tester)
{
        // Given
        string code = "(-(5%3)^2 + 7*3 - 6) / 5\n";
        BfLexer lexer = BfLexer();
        AstBuilder builder = AstBuilder();
        BfExecutor executor = BfExecutor();

        write_temp_bf_file( code );

        // When
        lexer.parseTokensFromFile( temp_file_name );
        BfNode * ast = builder.buildAst( lexer.getTokens() );
        executor.executeAst( ast );

        // Then
        tester.assertTrue( 3 == executor.currentNumber->getInt(), "3 == (-(5%3)^2 + 7*3 - 6) / 5" );
}

void given_an_assignment_when_we_execute_it_then_the_current_scope_contains_that_identifier(MiTester & tester)
{
	// Given
	string code = "food := 5\n";
        BfLexer lexer = BfLexer();
        AstBuilder builder = AstBuilder();
        BfExecutor executor = BfExecutor();

        write_temp_bf_file( code );

        // When
        lexer.parseTokensFromFile( temp_file_name );
        BfNode * ast = builder.buildAst( lexer.getTokens() );
        executor.executeAst( ast );

        // Then
        tester.assertTrue( executor.currentScope->containsIdentifier( "food" ) , "When assignments happen, the identifier is added to the current scope" );
}

void given_a_numeric_assignemnt_when_we_execute_it_then_the_value_can_be_retrieved_by_providing_the_variable_name(MiTester & tester)
{
	// Given
	string code = "food := 42\n";
	BfLexer lexer = BfLexer();
	AstBuilder builder = AstBuilder();
	BfExecutor executor = BfExecutor();

	write_temp_bf_file( code );

	// When
	lexer.parseTokensFromFile( temp_file_name );
        BfNode * ast = builder.buildAst( lexer.getTokens() );
        executor.executeAst( ast );

	// Then
	tester.assertTrue( 42 == executor.currentScope->getObjectByIdentifier( "food" )->getNumericValue()->getInt() ,"We can retrieve a variable's value from scope by using its name");
}

int main()
{
	MiTester tester = MiTester();

	given_some_code_with_just_a_number_when_it_is_run_then_the_stored_number_is_that_number( tester );
	given_some_code_with_just_a_math_operation_when_it_is_run_then_the_stored_number_is_that_number( tester );
	given_a_math_expression_with_a_negative_when_we_execute_it_then_the_expected_result_is_found( tester );
	given_a_complex_math_expression_when_we_execute_it_then_the_result_is_what_we_would_expect1( tester );
	given_a_complex_math_expression_when_we_execute_it_then_the_result_is_what_we_would_expect2( tester );
	given_an_assignment_when_we_execute_it_then_the_current_scope_contains_that_identifier( tester );
	given_a_numeric_assignemnt_when_we_execute_it_then_the_value_can_be_retrieved_by_providing_the_variable_name( tester );

	tester.printResults();
	return 0;
}
