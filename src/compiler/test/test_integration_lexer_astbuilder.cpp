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

	expected->appendChild(new BfIdentifier("say"));
	expected->appendChild(new BfString("\"Hello blowfish!\""));
	expected->appendChild(new BfNewline());

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

	plus->appendChild(new BfInteger("5"));
	plus->appendChild(new BfInteger("1"));

	expected->appendChild(plus);
	expected->appendChild(new BfNewline());

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

        plus->appendChild(new BfInteger("5"));
        plus->appendChild(new BfInteger("1"));

	minus->appendChild(plus);
	minus->appendChild(new BfInteger("2"));

        expected->appendChild(minus);
        expected->appendChild(new BfNewline());

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

	negative->appendChild(new BfInteger("2"));

        plus->appendChild(new BfInteger("5"));
        plus->appendChild(negative);

	expected->appendChild(plus);
        expected->appendChild(new BfNewline());

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

	multiply->appendChild(new BfFloat("1.5"));
	multiply->appendChild(new BfFloat("2.0"));

	plus->appendChild(new BfInteger("5"));
	plus->appendChild(multiply);

	expected->appendChild(plus);

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

	minus->appendChild(new BfInteger("5"));
	minus->appendChild(new BfInteger("2"));
	
	expected->appendChild(minus);

        // When
        lexer.parseTokensFromFile(temp_file_name);
        BfNode * ast = builder.buildAst(lexer.getTokens());

        // Then
        tester.assertTrue(haveSameNodeStructure(expected, ast), "Tree - subtraction, difficult to tell 5 - 2 from 5 -2");
}

void complexish_math_is_parsed_correctly(MiTester & tester, BfLexer lexer)
{
        // Given
        string code = "-(5.23 * -2 + -2.5)";
        AstBuilder builder = AstBuilder();

        write_temp_bf_file(code);

        BfRoot * expected = new BfRoot();
	BfExpression * exp1 = new BfExpression();
	BfMultiply * mult1 = new BfMultiply();
	BfNegative * neg1 = new BfNegative();
	BfNegative * neg2 = new BfNegative();
	BfNegative * neg3 = new BfNegative();
	BfPlus * plus1 = new BfPlus();

	neg1->appendChild(new BfInteger("2"));
	neg2->appendChild(new BfFloat("2.5"));

	mult1->appendChild(new BfFloat("5.23"));
	mult1->appendChild(neg1);

	plus1->appendChild(mult1);
	plus1->appendChild(neg2);

	exp1->appendChild(plus1);

	neg3->appendChild(exp1);

	expected->appendChild(neg3);

        // When
        lexer.parseTokensFromFile(temp_file_name);
        BfNode * ast = builder.buildAst(lexer.getTokens());

        // Then
        tester.assertTrue(haveSameNodeStructure(expected, ast), "Tree - somewhat complex expression");
}

void a_basic_mathematical_expression_with_a_fuction_in_it_is_parsed_into_an_ast_correctly(MiTester & tester, BfLexer lexer)
{
        // Given
        string code = "-5.34 * (sqrt 7)";
        AstBuilder builder = AstBuilder();

        write_temp_bf_file(code);

        BfRoot * expected = new BfRoot();
	BfMultiply * mult = new BfMultiply();
	BfExpression * exp = new BfExpression();
	BfNegative * neg = new BfNegative();

	exp->appendChild(new BfIdentifier("sqrt"));
	exp->appendChild(new BfInteger("7"));

	neg->appendChild(new BfFloat("5.34"));

	mult->appendChild(neg);
	mult->appendChild(exp);

	expected->appendChild(mult);

        // When
        lexer.parseTokensFromFile(temp_file_name);
        BfNode * ast = builder.buildAst(lexer.getTokens());

        // Then
        tester.assertTrue(haveSameNodeStructure(expected, ast), "Tree - negative float, multiplication, expression with sqrt function");
}

void a_basic_assignment_is_parsed_into_an_ast_correctly(MiTester & tester, BfLexer lexer)
{
        // Given
        string code = "my_var := 5";
        AstBuilder builder = AstBuilder();

        write_temp_bf_file(code);

        BfRoot * expected = new BfRoot();
	BfVariableAssignment * assign = new BfVariableAssignment();
	BfExpression * exp = new BfExpression();

	exp->appendChild(new BfIdentifier("my_var"));
	assign->appendChild(exp);
	assign->appendChild(new BfInteger("5"));

	expected->appendChild(assign);

        // When
        lexer.parseTokensFromFile(temp_file_name);
        BfNode * ast = builder.buildAst(lexer.getTokens());

        // Then
        tester.assertTrue(haveSameNodeStructure(expected, ast), "Tree - simple assignment");
}

void negative_expressions_are_parsed_correctly_into_an_ast(MiTester & tester, BfLexer lexer)
{
        // Given
        string code = "-(sqrt ofTheNumber: 5)";
        AstBuilder builder = AstBuilder();

        write_temp_bf_file(code);

        BfRoot * expected = new BfRoot();
	BfNegative * neg = new BfNegative();
	BfExpression * exp = new BfExpression();

	exp->appendChild(new BfIdentifier("sqrt"));
	exp->appendChild(new BfParameterIdentifier("ofTheNumber:"));
	exp->appendChild(new BfInteger("5"));

	neg->appendChild(exp);

	expected->appendChild(neg);

        // When
        lexer.parseTokensFromFile(temp_file_name);
        BfNode * ast = builder.buildAst(lexer.getTokens());

        // Then
        tester.assertTrue(haveSameNodeStructure(expected, ast), "Tree - negative float, multiplication, expression with sqrt function");
}

void embedded_expressions_are_parsed_correctly_into_an_ast(MiTester & tester, BfLexer lexer)
{
        // Given
        string code = "(sqrt (power 1.3 toThe: 5))";
        AstBuilder builder = AstBuilder();

        write_temp_bf_file(code);

        BfRoot * expected = new BfRoot();
        BfExpression * exp1 = new BfExpression();
	BfExpression * exp2 = new BfExpression();

	exp1->appendChild(new BfIdentifier("power"));
	exp1->appendChild(new BfFloat("1.3"));
	exp1->appendChild(new BfParameterIdentifier("toThe:"));
	exp1->appendChild(new BfInteger("5"));

	exp2->appendChild(new BfIdentifier("sqrt"));
	exp2->appendChild(exp1);

	expected->appendChild(exp2);

        // When
        lexer.parseTokensFromFile(temp_file_name);
        BfNode * ast = builder.buildAst(lexer.getTokens());

        // Then
        tester.assertTrue(haveSameNodeStructure(expected, ast), "Tree - negative float, multiplication, expression with sqrt function");
}

void a_simple_lambda_gets_parsed_correctly_into_an_ast(MiTester tester, BfLexer lexer)
{
        // Given
        string code = 	"lambda id: id fire [\n"
			"return 5\n"
			"]";

        AstBuilder builder = AstBuilder();

        write_temp_bf_file(code);

        BfRoot * expected = new BfRoot();
	BfLambda * lambda = new BfLambda();
	BfBlock * block = new BfBlock();

	block->appendChild(new BfNewline());
	block->appendChild(new BfReturn());
	block->appendChild(new BfInteger("5"));
	block->appendChild(new BfNewline());

	lambda->appendChild(new BfParameterIdentifier("id:"));
	lambda->appendChild(new BfIdentifier("id"));
	lambda->appendChild(new BfIdentifier("fire"));
	lambda->appendChild(block);

	expected->appendChild(lambda);

        // When
        lexer.parseTokensFromFile(temp_file_name);
        BfNode * ast = builder.buildAst(lexer.getTokens());

        // Then
        tester.assertTrue(haveSameNodeStructure(expected, ast), "Tree - lambda expression");
}

void popping_a_child_works(MiTester & tester)
{
	// Given
	BfNode * top = new BfNode();

	top->appendChild(new BfMinus());
	top->appendChild(new BfPlus());
	top->appendChild(new BfMultiply());

	// When
	top->popCurrentChild();

	// Then
	tester.assertTrue(top->numChildren() == 2, "When we pop a child, there should be N-1 left");
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
	complexish_math_is_parsed_correctly(tester, lex);
	a_basic_mathematical_expression_with_a_fuction_in_it_is_parsed_into_an_ast_correctly(tester, lex);
	a_basic_assignment_is_parsed_into_an_ast_correctly(tester, lex);
	negative_expressions_are_parsed_correctly_into_an_ast(tester, lex);
	embedded_expressions_are_parsed_correctly_into_an_ast(tester, lex);
	a_simple_lambda_gets_parsed_correctly_into_an_ast(tester, lex);
	popping_a_child_works(tester);

	tester.printResults();
	return 0;
}
