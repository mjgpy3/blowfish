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

	fout.open(temp_file_name.c_str());
	fout << text;
	fout.close();
}

void the_ast_thats_built_for_hello_world_looks_correct(MiTester & tester, BfLexer lexer, AstBuilder builder)
{
	string code = "say \"Hello blowfish!\"\n";

	write_temp_bf_file(code);
        lexer.parseTokensFromFile(temp_file_name);
        BfNode * ast = builder.buildAst(lexer.getTokens());

	BfRoot * expected = new BfRoot();

	(*expected).appendChild(new BfIdentifier("say"));
	(*expected).appendChild(new BfString("\"Hello blowfish!\""));
	(*expected).appendChild(new BfNewline());

	tester.assertTrue(haveSameNodeStructure(expected, ast), "Tree - hello world");
}


int main()
{
	MiTester tester = MiTester();
	BfLexer lex;
	AstBuilder build;

	the_ast_thats_built_for_hello_world_looks_correct(tester, lex, build);

	tester.printResults();
	return 0;
}
