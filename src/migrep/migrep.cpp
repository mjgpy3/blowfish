// Author: Michael Gilliland
#include <string>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include "migrep.h"
using namespace std;

//#define DEBUG

void MiGrepError(string message)
{
	cout << "MiGrep Error:" << endl;
	cout << message << endl;
	exit(1);
}

int numOccurrences(char me, string inMe)
{
	int result = 0;
	for (int i = 0; i < inMe.length(); i += 1)
	{
		if (inMe[i] == me && inMe[i-1] != '\\')
		{
			result += 1;
		}
	}
	return result;
}

void fillTwoPatternsFromSinglePipe(string & a, string & b, string pattern)
{
	string beg = "", end = "", ext1 = "", ext2 = "";
	string * side = &beg;
	string * orOpt = &ext1;

	for (int i = 0; i < pattern.length(); i += 1)
	{
		if (pattern[i] == '|')
		{
			side = &end;
			orOpt = &ext2;
		}
		else if (pattern[i] == '\\')
		{
			(*side).push_back(pattern[i]);
			(*side).push_back(pattern[i+1]);
			i += 1;
		}
		else if (pattern[i] == '(')
		{
			i += 1;
			while (pattern[i] != ')')
			{
				(*orOpt).push_back(pattern[i]);
				i += 1;
			}
		}
		else if (i != pattern.length()-1 && pattern[i+1] == '|')
		{
			(*orOpt).push_back(pattern[i]);
		}
		else if (i != 0 && pattern[i-1] == '|')
		{
			(*orOpt).push_back(pattern[i]);
		}
		else
		{
			(*side).push_back(pattern[i]);
		}
	}
	a = beg+ext1+end;
	b = beg+ext2+end;
}

bool MiGrep::isMatch(string text, string pattern)
{
	int numPipes = numOccurrences('|', pattern);
	vector<string> patterns;

	if (numPipes > 1)
	{
		MiGrepError("Only one OR '|' allowed in a pattern");
	}
	else if (numPipes == 1)
	{
		string pattern1, pattern2;
		fillTwoPatternsFromSinglePipe(pattern1, pattern2, pattern);
		patterns.push_back(pattern1);
		patterns.push_back(pattern2);
#ifdef DEBUG
		cout << "Patterns parsed from OR: " << endl;
		cout << '\t' << patterns[0] << endl;
		cout << '\t' << patterns[1] << endl;
#endif
	}
	else
	{
		patterns.push_back(pattern);
	}

	for (int j = 0; j < patterns.size(); j += 1)
	{
		MiGrepPattern miPattern = MiGrepPattern(patterns[j]);
		if (miPattern.matchesText(text))
		{
			return true;
		}
	}

	return false;
}

void MiGrepPattern::decrementCurrentCardinality()
{
	matchables[currentIndex].decrementCard();
}

bool MiGrepPattern::matchesText(string toMatch)
{
	cout << "Attempting to match: " << toMatch << endl;
	for (int i = 0; i < toMatch.length(); i += 1)
	{
		cout << "------------------------------\n";
		cout << " char: " << toMatch[i] << endl;
		cout << " current pattern is:\n";
		current().print();
		cout << "------------------------------\n";
		if (current().mustStopMatching())
		{
			cout << "  MUST STOP MATCHING WITH CURRENT" << endl;
			if (nextExists())
			{
				cout << "   Move next\n";
				moveNext();
				current().print();
			}
			else
			{
				cout << "   No more matches\n";
				return false;
			}
		}

		if (current().canStopMatching() && nextExists() && nextMatches(toMatch[i]))
		{
			cout << "  ->The next thing matches, we're moving\n";
			moveNext();
			decrementCurrentCardinality();
		}
		else if (current().matches(toMatch[i]))
		{
			cout << "  ->The current thing matches\n";
			decrementCurrentCardinality();
		}
		else
		{
			cout << "  ->Nothing matches\n";
			return false;
		}
	}

	current().print();
	cout << "Must stop matching: " << bool(!nextExists() && current().mustStopMatching()) << endl;

	return !nextExists() && (current().canStopMatching() || currentHasInfiniteCardinality());
}

bool MiGrepPattern::currentHasInfiniteCardinality()
{
	return matchables[currentIndex].hasInfiniteCardinality();
}

bool MiGrepChar::hasInfiniteCardinality()
{
	return card.restriction == infinite;
}

void decrementIfNotZero(int & me)
{
	if (me != 0)
	{
		me -= 1;
	}
}

bool MiGrepChar::mustStopMatching()
{
	return canStopMatching() && card.restriction != infinite && card.maximum == 0;
}

bool MiGrepChar::canStopMatching()
{
	return card.minimum == 0;
}

void MiGrepChar::decrementCard()
{
	decrementIfNotZero(card.minimum);
	decrementIfNotZero(card.maximum);
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
	return a == '}' || a == '{' ||
	    a == '[' || a == ']' ||
 	    a == '+' || a == '*' ||
	    a == '|' || a == '\\' ||
	    a == '.' || a == '(' ||
	    a == ')';
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

MiGrepPattern::MiGrepPattern(string patternText)
{
	fillMatchables(patternText);

	if (matchables.size() == 0)
	{
		MiGrepError("Must be given pattern text");
	}
	currentIndex = 0;
}

MiGrepChar MiGrepPattern::current()
{
	return matchables[currentIndex];
}

bool MiGrepPattern::nextExists()
{
	return currentIndex < (matchables.size()-1);
}

bool MiGrepPattern::currentMatches(char me)
{
	return matchables[currentIndex].matches(me);
}

bool MiGrepPattern::nextMatches(char me)
{
	return matchables[currentIndex+1].matches(me);
}	

void MiGrepPattern::moveNext()
{
	currentIndex += 1;
}

void MiGrepPattern::fillMatchables(string fromMe)
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
			MiGrepError(string("Malformed pattern: ") + factory.getBuildFrom());
		}
	}
}

void MiGrepChar::setCardinality(CardinalityType c, int min = 0, int max = 0)
{
	card.restriction = c;
	card.minimum = min;
	card.maximum = max;
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
	cout << "Card end:	 " << card.maximum << endl;
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
		cout << "BUILD FROM AFTER RANGE: " << buildFrom << endl;
	}

	// Cardinality

	if (buildFrom.length() == 0 || !isEngineToken(buildFrom[0]) || buildFrom[0] == '\\' || buildFrom[0] == '.')
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
	else
	{
		result.setCardinality(numeric, 1, 1);
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
