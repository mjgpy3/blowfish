#include <string>
#include <vector>
#include <iostream>
using namespace std;

#ifndef BLOWFISH_TOKENS
#define BLOWFISH_TOKENS

enum TokenName 
{
	t_identifier,
	t_param_ident,
	t_integer,
	t_float,
	t_char,
	t_string,
	t_white_space,
	t_op_plus,
	t_op_minus,
	t_op_times,
	t_op_divide,
	t_op_modulus,
	t_op_assign,
	t_line_ending,
	t_op_eq,
	t_op_lt,
	t_op_leq,
	t_op_gt,
	t_op_geq,
	t_pipe,
	t_kwd_module,
	t_kwd_class,
	t_kwd_meth,
	t_kwd_if,
	t_kwd_elseif,
	t_kwd_else,
	t_kwd_is,
	t_kwd_isnow,
	t_kwd_not,
	t_kwd_forms,
	t_kwd_are,
	t_kwd_or,
	t_kwd_and,
	t_kwd_for,
	t_kwd_enum,
	t_kwd_require,
	t_kwd_import,
	t_holder_begin,
	t_holder_end,
	t_block_begin,
	t_block_end,
	t_paren_begin,
	t_paren_end
};

struct Token 
{
	TokenName type;
	string match;
	bool isKeyword;
	bool savesText;
	bool isIgnored;
}; 

const int NUM_TOKENS = 43;

Token * AllTokens = new Token[NUM_TOKENS];

void setup_tokens()
{
	AllTokens[0].type = t_identifier;
	AllTokens[0].match = "[a-zA-Z0-9][a-zA-Z_]*";
	AllTokens[0].isKeyword = false;
	AllTokens[0].savesText = true;
	AllTokens[0].isIgnored = false;

	AllTokens[1].type = t_param_ident;
	AllTokens[1].match = "[a-zA-Z0-9][a-zA-Z_]*:";
	AllTokens[1].isKeyword = false;
	AllTokens[1].savesText = true;
	AllTokens[1].isIgnored = false;

	AllTokens[2].type = t_integer;
	AllTokens[2].match = "[0-9]+";
	AllTokens[2].isKeyword = false;
	AllTokens[2].savesText = true;
	AllTokens[2].isIgnored = false;

	AllTokens[3].type = t_float;
	AllTokens[3].match = "[0-9]*\\.[0-9]+";
	AllTokens[3].isKeyword = false;
	AllTokens[3].savesText = true;
	AllTokens[3].isIgnored = false;

	AllTokens[4].type = t_char;
	AllTokens[4].match = "\'.|\\.\'";
	AllTokens[4].isKeyword = false;
	AllTokens[4].savesText = false;
	AllTokens[4].isIgnored = false;

	AllTokens[5].type = t_string;
	AllTokens[5].match = "\".\"";
	AllTokens[5].isKeyword = false;
	AllTokens[5].savesText = false;
	AllTokens[5].isIgnored = false;

	AllTokens[6].type = t_white_space;
	AllTokens[6].match = "[\t ]+";
	AllTokens[6].isKeyword = false;
	AllTokens[6].savesText = false;
	AllTokens[6].isIgnored = true;

	AllTokens[7].type = t_op_plus;
	AllTokens[7].match = "+";
	AllTokens[7].isKeyword = false;
	AllTokens[7].savesText = false;
	AllTokens[7].isIgnored = false;

	AllTokens[8].type = t_op_minus;
	AllTokens[8].match = "-";
	AllTokens[8].isKeyword = false;
	AllTokens[8].savesText = false;
	AllTokens[8].isIgnored = false;

	AllTokens[9].type = t_op_times;
	AllTokens[9].match = "*";
	AllTokens[9].isKeyword = false;
	AllTokens[9].savesText = false;
	AllTokens[9].isIgnored = false;

	AllTokens[10].type = t_op_divide;
	AllTokens[10].match = "/";
	AllTokens[10].isKeyword = false;
	AllTokens[10].savesText = false;
	AllTokens[10].isIgnored = false;

	AllTokens[11].type = t_op_modulus;
	AllTokens[11].match = "%";
	AllTokens[11].isKeyword = false;
	AllTokens[11].savesText = false;
	AllTokens[11].isIgnored = false;

	AllTokens[12].type = t_op_assign;
	AllTokens[12].match = ":=";
	AllTokens[12].isKeyword = false;
	AllTokens[12].savesText = false;
	AllTokens[12].isIgnored = false;

	AllTokens[13].type = t_line_ending;
	AllTokens[13].match = "\n";
	AllTokens[13].isKeyword = false;
	AllTokens[13].savesText = false;
	AllTokens[13].isIgnored = false;

	AllTokens[14].type = t_op_eq;
	AllTokens[14].match = "=";
	AllTokens[14].isKeyword = false;
	AllTokens[14].savesText = false;
	AllTokens[14].isIgnored = false;

	AllTokens[15].type = t_op_lt;
	AllTokens[15].match = "<";
	AllTokens[15].isKeyword = false;
	AllTokens[15].savesText = false;
	AllTokens[15].isIgnored = false;

	AllTokens[16].type = t_op_leq;
	AllTokens[16].match = "<=";
	AllTokens[16].isKeyword = false;
	AllTokens[16].savesText = false;
	AllTokens[16].isIgnored = false;

	AllTokens[17].type = t_op_gt;
	AllTokens[17].match = ">";
	AllTokens[17].isKeyword = false;
	AllTokens[17].savesText = false;
	AllTokens[17].isIgnored = false;

	AllTokens[18].type = t_op_geq;
	AllTokens[18].match = ">=";
	AllTokens[18].isKeyword = false;
	AllTokens[18].savesText = false;
	AllTokens[18].isIgnored = false;

	AllTokens[19].type = t_pipe;
	AllTokens[19].match = "|";
	AllTokens[19].isKeyword = false;
	AllTokens[19].savesText = false;
	AllTokens[19].isIgnored = false;

	AllTokens[20].type = t_kwd_module;
	AllTokens[20].match = "module";
	AllTokens[20].isKeyword = true;
	AllTokens[20].savesText = false;
	AllTokens[20].isIgnored = false;

	AllTokens[21].type = t_kwd_class;
	AllTokens[21].match = "class";
	AllTokens[21].isKeyword = true;
	AllTokens[21].savesText = false;
	AllTokens[21].isIgnored = false;

	AllTokens[22].type = t_kwd_meth;
	AllTokens[22].match = "meth";
	AllTokens[22].isKeyword = true;
	AllTokens[22].savesText = false;
	AllTokens[22].isIgnored = false;

	AllTokens[23].type = t_kwd_if;
	AllTokens[23].match = "if";
	AllTokens[23].isKeyword = true;
	AllTokens[23].savesText = false;
	AllTokens[23].isIgnored = false;

	AllTokens[24].type = t_kwd_elseif;
	AllTokens[24].match = "elseif";
	AllTokens[24].isKeyword = true;
	AllTokens[24].savesText = false;
	AllTokens[24].isIgnored = false;

	AllTokens[25].type = t_kwd_else;
	AllTokens[25].match = "else";
	AllTokens[25].isKeyword = true;
	AllTokens[25].savesText = false;
	AllTokens[25].isIgnored = false;

	AllTokens[26].type = t_kwd_is;
	AllTokens[26].match = "is";
	AllTokens[26].isKeyword = true;
	AllTokens[26].savesText = false;
	AllTokens[26].isIgnored = false;

	AllTokens[27].type = t_kwd_isnow;
	AllTokens[27].match = "is_now";
	AllTokens[27].isKeyword = true;
	AllTokens[27].savesText = false;
	AllTokens[27].isIgnored = false;

	AllTokens[28].type = t_kwd_not;
	AllTokens[28].match = "not";
	AllTokens[28].isKeyword = true;
	AllTokens[28].savesText = false;
	AllTokens[28].isIgnored = false;

	AllTokens[29].type = t_kwd_forms;
	AllTokens[29].match = "forms";
	AllTokens[29].isKeyword = true;
	AllTokens[29].savesText = false;
	AllTokens[29].isIgnored = false;

	AllTokens[30].type = t_kwd_are;
	AllTokens[30].match = "are";
	AllTokens[30].isKeyword = true;
	AllTokens[30].savesText = false;
	AllTokens[30].isIgnored = false;

	AllTokens[31].type = t_kwd_or;
	AllTokens[31].match = "or";
	AllTokens[31].isKeyword = true;
	AllTokens[31].savesText = false;
	AllTokens[31].isIgnored = false;

	AllTokens[32].type = t_kwd_and;
	AllTokens[32].match = "and";
	AllTokens[32].isKeyword = true;
	AllTokens[32].savesText = false;
	AllTokens[32].isIgnored = false;

	AllTokens[33].type = t_kwd_for;
	AllTokens[33].match = "for";
	AllTokens[33].isKeyword = true;
	AllTokens[33].savesText = false;
	AllTokens[33].isIgnored = false;

	AllTokens[34].type = t_kwd_enum;
	AllTokens[34].match = "enum";
	AllTokens[34].isKeyword = true;
	AllTokens[34].savesText = false;
	AllTokens[34].isIgnored = false;

	AllTokens[35].type = t_kwd_require;
	AllTokens[35].match = "require";
	AllTokens[35].isKeyword = true;
	AllTokens[35].savesText = false;
	AllTokens[35].isIgnored = false;

	AllTokens[36].type = t_kwd_import;
	AllTokens[36].match = "import";
	AllTokens[36].isKeyword = true;
	AllTokens[36].savesText = false;
	AllTokens[36].isIgnored = false;

	AllTokens[37].type = t_holder_begin;
	AllTokens[37].match = "[lsd]{";
	AllTokens[37].isKeyword = false;
	AllTokens[37].savesText = false;
	AllTokens[37].isIgnored = false;

	AllTokens[38].type = t_holder_end;
	AllTokens[38].match = "}";
	AllTokens[38].isKeyword = false;
	AllTokens[38].savesText = false;
	AllTokens[38].isIgnored = false;

	AllTokens[39].type = t_block_begin;
	AllTokens[39].match = "[";
	AllTokens[39].isKeyword = false;
	AllTokens[39].savesText = false;
	AllTokens[39].isIgnored = false;

	AllTokens[40].type = t_block_end;
	AllTokens[40].match = "]";
	AllTokens[40].isKeyword = false;
	AllTokens[40].savesText = false;
	AllTokens[40].isIgnored = false;

	AllTokens[41].type = t_paren_begin;
	AllTokens[41].match = "(";
	AllTokens[41].isKeyword = false;
	AllTokens[41].savesText = false;
	AllTokens[41].isIgnored = false;

	AllTokens[42].type = t_paren_end;
	AllTokens[42].match = ")";
	AllTokens[42].isKeyword = false;
	AllTokens[42].savesText = false;
	AllTokens[42].isIgnored = false;

}

#endif

class FoundToken
{
public:
	Token * token;
	string value;
};

vector<FoundToken> tokenQueue;

void parseTokensFromFile(string fileName)
{
}

int main()
{
	cout << "Hello Lexer!\b";
	return 0;
}
