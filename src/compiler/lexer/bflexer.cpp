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

#include <string>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
#include "migrep.h"
#include "bflexer.h"
using namespace std;

#ifndef BLOWFISH_TOKENS
// Code in this section generated by bflexergen.py

#define BLOWFISH_TOKENS

const int NUM_TOKENS = 48;

int Ignore[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int SaveText[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

string Matches[] = {"class", "module", "meth", "if", "elseif", "else", "is", "is_now", "not", "forms", "are", "or", "and", "for", "enum", "require", "import", "until", "unless", "[a-zA-Z][a-zA-Z_]*:", "[0-9]+", "[0-9]+\\.[0-9]*", "'(.)|(\\\\[nt])'", "\".*\"", "[\\t ]", "\\+", "-", "\\*", "/", "%", ":=", "^", "\\+\\+", "\\.", "[a-zA-Z][a-zA-Z_]*", "\\n", "=", "<", "<=", ">", ">=", "\\|", "[lsd]\\{", "\\}", "\\[", "\\]", "\\(", "\\)"};

#endif

BfLexer::BfLexer()
{
	numTokens = NUM_TOKENS;
	AllTokens = new Token[NUM_TOKENS];
	setupTokens();
}

void BfLexer::setupTokens()
{
	for (int i = 0; i < numTokens; i += 1)
	{
		AllTokens[i].type = (TokenName)i;
	        AllTokens[i].match = Matches[i];
	        AllTokens[i].savesText = SaveText[i];
	        AllTokens[i].isIgnored = Ignore[i];
	}
}

FoundToken::FoundToken(Token & tok, string val)
{
	token = &tok;
	if ((*token).savesText)
	{
		value = val;
	}
}

void FoundToken::print()
{
	cout << (*token).match << " - ";
	if ((*token).savesText)
	{
		cout << value;
	}
	cout << endl;
}

bool BfLexer::matchesSomeToken(string value)
{
	MiGrep matcher;
	for (int i = 0; i < numTokens; i += 1)
	{
		//cout << "Trying to match with: " << i << endl;
		if (matcher.isMatch(value, AllTokens[i].match))
		{
			currentToken = &AllTokens[i];
			matchFound = true;
			return true;
		}
	}
	return false;
}

void BfLexer::parseTokensFromFile(string fileName)
{
	ifstream reader;
	string buffer;
	bool justCreatedNewBuffer = false;

	reader.open(fileName.c_str());

	if (!reader)
	{
		cout << "File \"" + fileName + "\" does not exist!";
		exit(1);
	}

	while (!reader.eof())
	{
		if (!justCreatedNewBuffer)
		{
			buffer.push_back(reader.get());
		}
		cout << "Processing: (" << buffer << ')' << endl;
		matchFound = false;
		while (matchesSomeToken(buffer))
		{
			buffer.push_back(reader.get());
			cout << "(IN WHILE) Processing: (" << buffer << ')' << endl;
		}
		if (matchFound)
		{
			cout << "--------->Found match with type: " <<  (*currentToken).type << " with pattern: /" << (*currentToken).match << "/" << endl;
			if (!(*currentToken).isIgnored)
			{
				foundTokens.push_back(FoundToken(*currentToken, buffer.substr(0, buffer.length()-1)));
			}

			// Buffer needs to be where the match stopped
			char endOfBuffer = buffer[buffer.length()-1];
			buffer = "";
			buffer.push_back(endOfBuffer);
			justCreatedNewBuffer = true;
			cout << "New buffer: (" << buffer << ")" << endl;
		}
		else
		{
			justCreatedNewBuffer = false;
		}
	}
}

int main()
{
	cout << "Hello Lexer!\n";
	BfLexer lexer = BfLexer();

        int a[] = {1,2,3,4};
	lexer.parseTokensFromFile(string("test.st"));

	return 0;
}
