// Author: Michael Gilliland
#include <string>
#include <iostream>
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
	    a == '-' || a == '|' ||
	    a == ',')
	{
		return true;
	}

	return false;
}

bool locationExists(string thing, int location)
{
	return (location >= 0 && location < thing.length());
}

MiGrepChar MiGrepCharFactory::buildNext()
{
	MiGrepChar result = MiGrepChar();

	for (int i = 0; i < buildFrom.length(); i += 1)
	{
		char currentChar = buildFrom[i];

		if (!isEngineToken(currentChar))
		{
		}
		else
		{
		}
	}

	return result;
}

bool MiGrepCharFactory::doneBuilding()
{
	return buildFrom.length() == 0;
}
