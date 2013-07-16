#include <string>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
#include "migrep.h"
using namespace std;

#ifndef BLOWFISH_TOKENS
// Code in this section generated by bflexergen.py

#define BLOWFISH_TOKENS

enum TokenName 
{
	t_identifier, t_param_ident, t_integer, t_float, t_char, t_string, t_white_space, t_op_plus, t_op_minus, t_op_times, t_op_divide, t_op_modulus, t_op_assign, t_op_pow, t_op_concat, t_line_ending, t_op_eq, t_op_lt, t_op_leq, t_op_gt, t_op_geq, t_pipe, t_kwd_module, t_kwd_class, t_kwd_meth, t_kwd_if, t_kwd_elseif, t_kwd_else, t_kwd_is, t_kwd_isnow, t_kwd_not, t_kwd_forms, t_kwd_are, t_kwd_or, t_kwd_and, t_kwd_for, t_kwd_enum, t_kwd_require, t_kwd_import, t_kwd_until, t_kwd_unless, t_holder_begin, t_holder_end, t_block_begin, t_block_end, t_paren_begin, t_paren_end
};

struct Token 
{
	TokenName type;
	string match;
	bool isKeyword;
	bool savesText;
	bool isIgnored;
}; 

const int NUM_TOKENS = 47;

Token * AllTokens = new Token[NUM_TOKENS];

int Ignore[] = {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int Keyword[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0};
int SaveText[] = {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

string Matches[] = {"[a-zA-Z0-9][a-zA-Z_]*", "[a-zA-Z0-9][a-zA-Z_]*:", "[0-9]+", "[0-9]*\\.[0-9]+", "'(.)|(\\\\[nt])'", "\".\"", "[\\t ]+", "\\+", "-", "\\*", "/", "%", ":=", "^", "\\+\\+", "\\n", "=", "<", "<=", ">", ">=", "\\|", "module", "class", "meth", "if", "elseif", "else", "is", "is_now", "not", "forms", "are", "or", "and", "for", "enum", "require", "import", "until", "unless", "[lsd]\\{", "\\}", "\\[", "\\]", "\\(", "\\)"};

void init_token(int index)
{
	AllTokens[index].type = (TokenName)index;
	AllTokens[index].match = Matches[index];
	AllTokens[index].isKeyword = Keyword[index];
	AllTokens[index].savesText = SaveText[index];
	AllTokens[index].isIgnored = Ignore[index];
}

void setup_tokens()
{
	for (int i = 0; i < NUM_TOKENS; i += 1)
	{
		init_token(i);
	}
}

#endif

class FoundToken
{
public:
	FoundToken(Token & tok, string val)
	{
		token = &tok;
		if ((*token).savesText)
		{
			value = val;
		}
	}
private:
	Token * token;
	string value;
};

vector<FoundToken> foundTokens;
Token * currentToken;
bool matchFound;

bool matchesSomeToken(string value)
{
	MiGrep matcher;
	for (int i = 0; i < NUM_TOKENS; i += 1)
	{
		cout << "Trying to match with: " << i << endl;
		if (matcher.isMatch(value, AllTokens[i].match))
		{
			currentToken = &AllTokens[i];
			matchFound = true;
			return true;
		}
	}
	return false;
}

void parseTokensFromFile(string fileName)
{
	ifstream reader;
	string buffer;

	reader.open(fileName.c_str());

	if (!reader)
	{
		cout << "File \"" + fileName + "\" does not exist!";
		exit(1);
	}

	while (!reader.eof())
	{
		buffer.push_back(reader.get());

		cout << "Processing: " << buffer << endl;
		matchFound = false;
		while (matchesSomeToken(buffer))
		{
			buffer.push_back(reader.get());
			cout << "Processing: " << buffer << endl;
		}

		if (matchFound)
		{
			foundTokens.push_back(FoundToken(*currentToken, buffer.substr(0, buffer.length()-1)));

			// Buffer needs to be where the match stopped
			char endOfBuffer = buffer[buffer.length()-1];
			buffer = "";
			buffer.push_back(endOfBuffer);
		}
	}
}

int main()
{
	setup_tokens();
	cout << "Hello Lexer!\n";

        int a[] = {1,2,3,4};
	parseTokensFromFile(string("test.txt"));

	return 0;
}
