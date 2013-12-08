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

void given_a_numeric_assignment_when_we_execute_it_then_the_value_can_be_retrieved_by_providing_the_variable_name(MiTester & tester)
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

void given_an_assignment_and_then_an_expression_containing_that_assignement_when_we_execute_the_value_is_calculated_correctly(MiTester & tester)
{
	// Given
        string code = 	"answer := 42\n"
			"two_answers := 2 * answer";

        BfLexer lexer = BfLexer();
        AstBuilder builder = AstBuilder();
        BfExecutor executor = BfExecutor();

        write_temp_bf_file( code );

        // When
        lexer.parseTokensFromFile( temp_file_name );
        BfNode * ast = builder.buildAst( lexer.getTokens() );
        executor.executeAst( ast );

        // Then
	tester.assertTrue( 84 == executor.currentScope->getObjectByIdentifier( "two_answers" )->getNumericValue()->getInt() ,"Vars can be used to make other vars");
}

void given_an_assignment_of_a_number_to_a_variable_when_we_execute_it_then_the_variables_type_is_number(MiTester & tester)
{
	// Given
	string code = "variable := 42";

	BfLexer lexer = BfLexer();
        AstBuilder builder = AstBuilder();
        BfExecutor executor = BfExecutor();

        write_temp_bf_file( code );

        // When
        lexer.parseTokensFromFile( temp_file_name );
        BfNode * ast = builder.buildAst( lexer.getTokens() );
        executor.executeAst( ast );

        // Then
        tester.assertEqual( "Number", executor.currentScope->getObjectByIdentifier( "variable" )->getTypeName() ,"Vars assigned to numeric literals can be found to be of type: Number");
}

void given_an_assignment_of_a_string_to_a_variable_when_we_execute_it_then_the_string_value_can_be_gotten_by_the_identifier(MiTester & tester)
{
	// Given
	string code = "name := 'Walt'";

        BfLexer lexer = BfLexer();
        AstBuilder builder = AstBuilder();
        BfExecutor executor = BfExecutor();

        write_temp_bf_file( code );

        // When
        lexer.parseTokensFromFile( temp_file_name );
        BfNode * ast = builder.buildAst( lexer.getTokens() );
        executor.executeAst( ast );

        // Then
        tester.assertEqual( "Walt", executor.currentScope->getObjectByIdentifier( "name" )->getStringValue()->getString() ,"Variable's string value can be retrieved");
}

void given_an_assignment_to_a_type_then_a_reassignment_to_a_different_type_when_we_execute_it_then_the_second_type_holds(MiTester & tester)
{
	// Given
	string code =   "name := 'Walt'\n"
			"name := 5\n";

        BfLexer lexer = BfLexer();
        AstBuilder builder = AstBuilder();
        BfExecutor executor = BfExecutor();

        write_temp_bf_file( code );

        // When
        lexer.parseTokensFromFile( temp_file_name );
        BfNode * ast = builder.buildAst( lexer.getTokens() );
        executor.executeAst( ast );

        // Then
        tester.assertEqual( "Number", executor.currentScope->getObjectByIdentifier( "name" )->getTypeName(),"Variables don't really care about type reassignment");
}

void given_some_code_describing_a_show_method_being_called_on_a_number_when_that_code_is_executed_then_the_resultant_object_has_a_type_of_string(MiTester & tester)
{
	// Given
        string code =   "a_string := 42.show\n";

        BfLexer lexer = BfLexer();
        AstBuilder builder = AstBuilder();
        BfExecutor executor = BfExecutor();

        write_temp_bf_file( code );

        // When
        lexer.parseTokensFromFile( temp_file_name );
        BfNode * ast = builder.buildAst( lexer.getTokens() );
        executor.executeAst( ast );

        // Then
        tester.assertEqual( "String", executor.currentScope->getObjectByIdentifier( "a_string" )->getTypeName(), "Calling a type converting method works");
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
	given_a_numeric_assignment_when_we_execute_it_then_the_value_can_be_retrieved_by_providing_the_variable_name( tester );
	given_an_assignment_and_then_an_expression_containing_that_assignement_when_we_execute_the_value_is_calculated_correctly( tester );
	given_an_assignment_of_a_number_to_a_variable_when_we_execute_it_then_the_variables_type_is_number( tester );
	given_an_assignment_of_a_string_to_a_variable_when_we_execute_it_then_the_string_value_can_be_gotten_by_the_identifier( tester );
	given_an_assignment_to_a_type_then_a_reassignment_to_a_different_type_when_we_execute_it_then_the_second_type_holds( tester );
	given_some_code_describing_a_show_method_being_called_on_a_number_when_that_code_is_executed_then_the_resultant_object_has_a_type_of_string( tester );

	tester.printResults();
	return 0;
}
