// Author: Michael Gilliland
#include <string>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include "migrep.h"
using namespace std;

//#define DEBUG

bool MiGrep::isMatch(string text, string pattern)
{

	fillMatchables(pattern);

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

string MiGrepCharFactory::getBuildFrom()
{
	return buildFrom;
}

void MiGrep::fillMatchables(string fromMe)
{
	MiGrepCharFactory factory = MiGrepCharFactory(fromMe);

	while (!factory.doneBuilding())
	{
		try
		{
			matchables.push_back(factory.buildNext());
		}
		catch (...)
		{
			cout << string("MiGrepError:\nMalformed pattern: ") + factory.getBuildFrom();
		}
	}
}

void MiGrepChar::setCardinality(CardinalityType c, int min = 0, int max = 0)
{
	card.restriction = c;
	card.minimum = min;
	card.maximum = max;
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

bool isCardinalityToken(char me)
{
	return me == '+' || me == '{' ||
		me == '*';
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

char getEscapedChar(char pivot)
{
	if (pivot == 'n')
	{
		return '\n';
	}
	if (pivot == 't')
	{
		return '\t';
	}

	return pivot;
}

int buildRanges(MiGrepChar & miGrep, string fromMe)
{
	for (int i = 1; i < fromMe.length(); i += 1)
	{
#ifdef DEBUG
		cout << "Processing Range: " << fromMe[i] << endl;
#endif
		if (fromMe[i] == ']')
		{
			cout << "Matches ]\n";
			return i+1;
		}
		else if (fromMe[i] == '\\')
		{
			char literal = getEscapedChar(fromMe[i+1]);
			miGrep.addRange(Range(literal, literal));
			i += 1;
		}
		else if (fromMe[i+1] != '-')
		{
			miGrep.addRange(Range(fromMe[i], fromMe[i]));
		}
		else if (fromMe[i+1] == '-')
		{
			miGrep.addRange(Range(fromMe[i], fromMe[i+2]));
			i += 2;
		}
	}
	return 0;
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
			break;
		}
		else if (fromMe[i] != ' ')
		{
			MiGrepError("Cardinality block not formed properly");
		}
	}
	miChar.setCardinality(numeric, min, max);
	return i;
}

void Range::print()
{
	cout << "'" << begin << "'" << "-" << "'" << end << "'";
}

void MiGrepChar::print()
{
	cout << "Ranges: " << endl;

	for (int i = 0; i < ranges.size(); i += 1)
	{
		cout << "\t";
		ranges[i].print();
		cout << endl;
	}
	cout << "Cardinality type: " << card.restriction << endl;
	cout << "Card start:       " << card.minimum << endl;
	cout << "Card end:         " << card.maximum << endl;
	cout << "Card required:    " << card.mustMatch << endl;
	
}

MiGrepChar MiGrepCharFactory::buildNext()
{
	MiGrepChar result = MiGrepChar();
#ifdef DEBUG
	cout << "Processing: " << buildFrom << endl;
#endif

	if (!isEngineToken(buildFrom[0]))
	{
		result.addRange(Range(buildFrom[0], buildFrom[0]));
		buildFrom = buildFrom.substr(1);
	}
	else if (buildFrom[0] == '.')
	{
		result.addRange(Range(char(0), char(126)));
		buildFrom = buildFrom.substr(1);
	}
	else if (buildFrom[0] == '\\')
	{
		if (!locationExists(buildFrom, 1))
		{
			MiGrepError("Cannot escape at the end of a pattern");
		}
		char literal = getEscapedChar(buildFrom[1]);
		result.addRange(Range(literal, literal));
		buildFrom = buildFrom.substr(2);
	}
	else if (buildFrom[0] == '[')
	{
		buildFrom = buildFrom.substr(buildRanges(result, buildFrom));
	}

	// Cardinality

	if (buildFrom.length() == 0 || !isEngineToken(buildFrom[0]) || buildFrom[0] == '\\')
	{
		result.setCardinality(numeric, 1, 1);
	}
	else if (buildFrom[0] == '+')
        {
                result.setCardinality(infinite, 1, 0);
                buildFrom = buildFrom.substr(1);
        }
        else if (buildFrom[0] == '*')
        {
                result.setCardinality(infinite, 0, 0);
                buildFrom = buildFrom.substr(1);
        }
        else if (buildFrom[0] == '{')
        {
                buildFrom =
                        buildFrom.substr(1+parseCardinalityToMiGrepChar(result, buildFrom));
        }

#ifdef DEBUG
	cout << "Generated MiGrepChar: " << endl;
	result.print();
#endif

	return result;
}

bool MiGrepCharFactory::doneBuilding()
{
	return buildFrom.length() == 0;
}
