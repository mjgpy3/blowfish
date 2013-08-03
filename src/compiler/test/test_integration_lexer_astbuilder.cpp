#include <fstream>
#include <string>
#include "mitest.h"
#include "bflexer.h"
#include "astbuilder.h"
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

void the_ast_thats_built_for_hello_world_is_correct(MiTester & tester, BfLexer lexer)
{
	// Given
	string code = "say \"Hello blowfish!\"\n";
	AstBuilder builder = AstBuilder();

	write_temp_bf_file(code);

	BfRoot * expected = new BfRoot();

	(*expected).appendChild(new BfIdentifier("say"));
	(*expected).appendChild(new BfString("\"Hello blowfish!\""));
	(*expected).appendChild(new BfNewline());

	// When
        lexer.parseTokensFromFile(temp_file_name);
        BfNode * ast = builder.buildAst(lexer.getTokens());

	// Then
	tester.assertTrue(haveSameNodeStructure(expected, ast), "Tree - hello world");
}

void the_ast_thats_built_for_a_simple_math_operation_is_correct(MiTester & tester, BfLexer lexer)
{
	// Given
	string code = "5 + 1\n";
	AstBuilder builder = AstBuilder();

        write_temp_bf_file(code);

        BfRoot * expected = new BfRoot();
	BfPlus * plus = new BfPlus();

	(*plus).appendChild(new BfInteger("5"));
	(*plus).appendChild(new BfInteger("1"));

	(*expected).appendChild(plus);
	(*expected).appendChild(new BfNewline());

	// When
        lexer.parseTokensFromFile(temp_file_name);
        BfNode * ast = builder.buildAst(lexer.getTokens());

	// Then
        tester.assertTrue(haveSameNodeStructure(expected, ast), "Tree - addition");
}

void simple_asts_with_operation_chaining_when_ooo_is_same_are_right_to_left(MiTester & tester, BfLexer lexer)
{
	// Given
        string code = "5 + 1 - 2\n";
        AstBuilder builder = AstBuilder();

        write_temp_bf_file(code);

        BfRoot * expected = new BfRoot();
        BfPlus * plus = new BfPlus();
	BfMinus * minus = new BfMinus();

        (*plus).appendChild(new BfInteger("5"));
        (*plus).appendChild(new BfInteger("1"));

	(*minus).appendChild(plus);
	(*minus).appendChild(new BfInteger("2"));

        (*expected).appendChild(minus);
        (*expected).appendChild(new BfNewline());

        // When
        lexer.parseTokensFromFile(temp_file_name);
        BfNode * ast = builder.buildAst(lexer.getTokens());

        // Then
        tester.assertTrue(haveSameNodeStructure(expected, ast), "Tree - addition then subtraction");
}

void mathematical_asts_with_negative_numbers_are_handled_alright(MiTester & tester, BfLexer lexer)
{
        // Given
        string code = "5 + -2\n";
        AstBuilder builder = AstBuilder();

        write_temp_bf_file(code);

        BfRoot * expected = new BfRoot();
        BfPlus * plus = new BfPlus();
        BfNegative * negative = new BfNegative();

	(*negative).appendChild(new BfInteger("2"));

        (*plus).appendChild(new BfInteger("5"));
        (*plus).appendChild(negative);

	(*expected).appendChild(plus);
        (*expected).appendChild(new BfNewline());

        // When
        lexer.parseTokensFromFile(temp_file_name);
        BfNode * ast = builder.buildAst(lexer.getTokens());

        // Then
        tester.assertTrue(haveSameNodeStructure(expected, ast), "Tree - addition where one is negative");
}

void asts_with_differently_ordered_operations_are_handled_properly(MiTester & tester, BfLexer lexer)
{
        // Given
        string code = "5 + 1.5 * 2.0";
        AstBuilder builder = AstBuilder();

        write_temp_bf_file(code);

        BfRoot * expected = new BfRoot();
        BfPlus * plus = new BfPlus();
        BfMultiply * multiply = new BfMultiply();

	(*multiply).appendChild(new BfFloat("1.5"));
	(*multiply).appendChild(new BfFloat("2.0"));

	(*plus).appendChild(new BfInteger("5"));
	(*plus).appendChild(multiply);

	(*expected).appendChild(plus);

        // When
        lexer.parseTokensFromFile(temp_file_name);
        BfNode * ast = builder.buildAst(lexer.getTokens());

        // Then
        tester.assertTrue(haveSameNodeStructure(expected, ast), "Tree - addition then multiplication (scattered floats)");
}

void there_is_differentiation_between_negative_terms_when_there_are_no_spaces(MiTester & tester, BfLexer lexer)
{
        // Given
        string code = "5-2";
        AstBuilder builder = AstBuilder();

        write_temp_bf_file(code);

        BfRoot * expected = new BfRoot();
	BfMinus * minus = new BfMinus();

	(*minus).appendChild(new BfInteger("5"));
	(*minus).appendChild(new BfInteger("2"));
	
	(*expected).appendChild(minus);

        // When
        lexer.parseTokensFromFile(temp_file_name);
        BfNode * ast = builder.buildAst(lexer.getTokens());

        // Then
        tester.assertTrue(haveSameNodeStructure(expected, ast), "Tree - subtraction, difficult to tell 5 - 2 from 5 -2");
}


int main()
{
	MiTester tester = MiTester();
	BfLexer lex;

	the_ast_thats_built_for_hello_world_is_correct(tester, lex);
	the_ast_thats_built_for_a_simple_math_operation_is_correct(tester, lex);
	simple_asts_with_operation_chaining_when_ooo_is_same_are_right_to_left(tester, lex);
	mathematical_asts_with_negative_numbers_are_handled_alright(tester, lex);
	asts_with_differently_ordered_operations_are_handled_properly(tester, lex);
	there_is_differentiation_between_negative_terms_when_there_are_no_spaces(tester, lex);

	tester.printResults();
	return 0;
}
