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

#ifndef BLOWFISH_LEXER
#define BLOWFISH_LEXER

#include <string>
#include <vector>
using namespace std;

#ifndef BLOWFISH_TOKEN_NAMES
#define BLOWFISH_TOKEN_NAMES

enum TokenName 
{
	t_kwd_class, t_kwd_module, t_kwd_meth, t_kwd_if, t_kwd_elseif, t_kwd_else, t_kwd_is, t_kwd_isnow, t_kwd_not, t_kwd_forms, t_kwd_are, t_kwd_or, t_kwd_and, t_kwd_for, t_kwd_enum, t_kwd_require, t_kwd_import, t_kwd_until, t_kwd_unless, t_param_ident, t_integer, t_float, t_char, t_string, t_white_space, t_op_plus, t_op_minus, t_op_times, t_op_divide, t_op_modulus, t_op_assign, t_op_pow, t_op_concat, t_op_dot, t_identifier, t_line_ending, t_op_eq, t_op_lt, t_op_leq, t_op_gt, t_op_geq, t_pipe, t_holder_begin, t_holder_end, t_block_begin, t_block_end, t_paren_begin, t_paren_end
};

#endif

struct Token
{
        TokenName type;
        string match;
        bool savesText;
        bool isIgnored;
};

class FoundToken
{
public:
	FoundToken(Token & tok, string val);
	void print();
private:
        Token * token;
        string value;
};

class BfLexer
{
public:
	BfLexer();
	void setupTokens();
	bool matchesSomeToken(string value);
	void parseTokensFromFile(string fileName);

private:
	Token * AllTokens;
	vector<FoundToken> foundTokens;
	Token * currentToken;
	int numTokens;
	bool matchFound;
};

#endif
