// Author: Michael Gilliland
#include <string>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include "migrep.h"
using namespace std;


bool MiGrep::isMatch(string text, string pattern)
{
	// TODO: Keep current, look for current and next

	if (pattern.compare(".+") == 0)
	{
		return true;
	}

	for (int i = 0; i < text.length(); i += 1)
	{
		if (!(pattern[i] == text[i] || pattern[i] == '.'))
		{
			return false;
		}
	}

	return true;
}

Range::Range(char b, char e)
{
	begin = b;
	end = e;
}

bool Range::includes(char me)
{
	return (me >= begin && me <= end);
}

MiGrepChar::MiGrepChar()
{
}

MiGrepCharFactory::MiGrepCharFactory(string patternText)
{
	buildFrom = patternText;
}

bool isEngineToken(char a)
{
	if (a == '}' || a == '{' ||
            a == '[' || a == ']' ||
 	    a == '+' || a == '*' ||
	    a == '|' || a == '\\' ||
            a == '.' || a == '(' ||
            a == ')')
	{
		return true;
	}

	return false;
}

bool locationExists(string thing, int location)
{
	return (location >= 0 && location < thing.length());
}

void MiGrepChar::addRange(Range r)
{
	ranges.push_back(r);
}

bool MiGrepChar::matches(char me)
{
	for (int i = 0; i < ranges.size(); i += 1)
	{
		if (ranges[i].includes(me))
		{
			return true;
		}
	}
	return false;
}

void MiGrepChar::setCardinality(CardinalityType c, int min = 0, int max = 0)
{
	card.restriction = c;
	card.minimum = min;
	card.minimum = max;
	card.mustMatch = min;
}

void MiGrepError(string message)
{
	cout << "MiGrep Error:" << endl;
	cout << message << endl;
	exit(1);
}

bool nextCharacterIs(string thing, int i, char me)
{
	return locationExists(thing, i+1) && thing[i+1] == me;
}

bool isNumericCommaOrSpace(char me)
{
	if ((me >= '0' && me <= '9') ||
             me == ',' || me == ' ')
	{
		return true;
	}
	return false;
}

int charsIntValue(char digit)
{
	return int(digit) - 48;
}

int MiAToI(string thing)
{
	int result = 0;
	for (int i = 0; i < thing.length(); i += 1)
	{
		result = result*10 +  charsIntValue(thing[i]);
	}
	return result;
}

int parseCardinalityToMiGrepChar(MiGrepChar & miChar, string fromMe)
{
	int * ptr;
	int min = 0, max = 0, i;
	ptr = &min;
	string b;

	for (i = 1; i <= fromMe.length(); i += 1)
	{
		if (isdigit(fromMe[i]))
		{
			b.push_back(fromMe[i]);
		}
		else if (fromMe[i] == ',')
		{
			*ptr = MiAToI(b);
			b = "";
			ptr = &max;
		}
		else if (fromMe[i] == '}')
		{
			*ptr = MiAToI(b);
		}
		else if (fromMe[i] != ' ')
		{
			MiGrepError("Cardinality block not formed properly");
		}
	}
	miChar.setCardinality(numeric, min, max);
	return i;
}

MiGrepChar MiGrepCharFactory::buildNext()
{
	MiGrepChar result = MiGrepChar();

	for (int i = 0; i < buildFrom.length(); i += 1)
	{
		char currentChar = buildFrom[i];

		// The next spot exists and is a literal
		if (locationExists(buildFrom, i+1) && !isEngineToken(buildFrom[i+1]))
		{
			result.addRange(Range(currentChar, currentChar));
			result.setCardinality(numeric, 1, 1);
			buildFrom = buildFrom.substr(i+1);
			break;
		}
		// The next spot exists and is '+'
		else if (nextCharacterIs(buildFrom, i, '+'))
		{
			result.addRange(Range(currentChar, currentChar));
			result.setCardinality(infinite, 1);
			buildFrom = buildFrom.substr(i+2);
			break;
		}
		// The next spot exists and is '*'
		else if (nextCharacterIs(buildFrom, i, '*'))
		{
			result.addRange(Range(currentChar, currentChar));
			result.setCardinality(infinite);
			buildFrom = buildFrom.substr(i+2);
			break;
		}
		// The next spot exists and is '{'
		else if (nextCharacterIs(buildFrom, i, '{'))
		{
			result.addRange(Range(currentChar, currentChar));
			buildFrom = 
				buildFrom.substr(parseCardinalityToMiGrepChar(result, buildFrom.substr(i)));
			break;
		}
		// If at last character and is literal
		else if (i == buildFrom.length()-1 && !isEngineToken(currentChar))
		{
			result.addRange(Range(currentChar, currentChar));
			result.setCardinality(numeric, 1, 1);
			buildFrom = "";
			break;
		}
	}

	return result;
}

bool MiGrepCharFactory::doneBuilding()
{
	return buildFrom.length() == 0;
}
