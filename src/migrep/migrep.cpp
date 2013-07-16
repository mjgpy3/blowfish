// Author: Michael Gilliland
#include <string>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include "migrep.h"
using namespace std;

//#define DEBUG

//!
//! How many times does the given character occur in the given string?
//!
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

//!
//! Given pattern text with a single pipe, fill the given strings with the two patterns resulting from the pipe's OR operation (PCFR)
//!
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

//!
//! Is the given text matched by the given pattern?
//!
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
		////cout << "Patterns parsed from OR: " << endl;
		//cout << '\t' << patterns[0] << endl;
		//cout << '\t' << patterns[1] << endl;
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

//!
//! Decrement the cardinality of the current MiGrepChar
//!
void MiGrepPattern::decrementCurrentCardinality()
{
	matchables[currentIndex].decrementCard();
}

//!
//! Does this MiGrepPattern match the given text?
//!
bool MiGrepPattern::matchesText(string toMatch)
{
	//cout << "Attempting to match: " << toMatch << endl;
	for (int i = 0; i < toMatch.length(); i += 1)
	{
		//cout << "------------------------------\n";
		//cout << " char: " << toMatch[i] << endl;
		//cout << " current pattern is:\n";
		current().print();
		//cout << "------------------------------\n";
		if (current().mustStopMatching())
		{
			//cout << "  MUST STOP MATCHING WITH CURRENT" << endl;
			if (nextExists())
			{
				//cout << "   Move next\n";
				moveNext();
				current().print();
			}
			else
			{
				//cout << "   No more matches\n";
				return false;
			}
		}

		if (current().canStopMatching() && nextExists() && nextMatches(toMatch[i]))
		{
			//cout << "  ->The next thing matches, we're moving\n";
			moveNext();
			decrementCurrentCardinality();
		}
		else if (current().matches(toMatch[i]))
		{
			//cout << "  ->The current thing matches\n";
			decrementCurrentCardinality();
		}
		else
		{
			//cout << "  ->Nothing matches\n";
			return false;
		}
	}

	current().print();
	//cout << "Must stop matching: " << bool(!nextExists() && current().mustStopMatching()) << endl;

	// TODO: Need to check and see if next is last and next is *
	return !nextExists() && (current().canStopMatching() || currentHasInfiniteCardinality());
}

//!
//! Does the current MiGrepChar have infinite cardinality?
//!
bool MiGrepPattern::currentHasInfiniteCardinality()
{
	return matchables[currentIndex].hasInfiniteCardinality();
}

//!
//! Does this MiGrepChar have infinite cardinality?
//!
bool MiGrepChar::hasInfiniteCardinality()
{
	return card.restriction == infinite;
}

//!
//! Decrements the passed number iff it's not already zero
//!
void decrementIfNotZero(int & me)
{
	if (me != 0)
	{
		me -= 1;
	}
}

//!
//! This MiGrepChar has hit the maximum amount of matches it can perform
//!
bool MiGrepChar::mustStopMatching()
{
	return canStopMatching() && card.restriction != infinite && card.maximum == 0;
}

//!
//! This MiGrepChar can be done matching
//!
bool MiGrepChar::canStopMatching()
{
	return card.minimum == 0;
}

//!
//! If the cardinality's values are not zero, decrement them
//!
void MiGrepChar::decrementCard()
{
	decrementIfNotZero(card.minimum);
	decrementIfNotZero(card.maximum);
}

//!
//! Initializes a new instance of Range
//!
Range::Range(char b, char e)
{
	begin = b;
	end = e;
}

//!
//! Does this range contain (inclusively) the asked for char?
//!
bool Range::includes(char me)
{
	return (me >= begin && me <= end);
}

//!
//! Initializes a new instance of MiGrepChar
//!
MiGrepChar::MiGrepChar()
{
}

//!
//! Initializes a new instance of MiGrepCharFactory by storing the passed pattern's text
//!
MiGrepCharFactory::MiGrepCharFactory(string patternText)
{
	buildFrom = patternText;
}

//!
//! True if the given character has special meaning in the token engine
//!
bool isEngineToken(char a)
{
	return a == '}' || a == '{' ||
	    a == '[' || a == ']' ||
 	    a == '+' || a == '*' ||
	    a == '|' || a == '\\' ||
	    a == '.' || a == '(' ||
	    a == ')';
}

//!
//! In the given string, does the asked for location exist?
//!
bool locationExists(string thing, int location)
{
	return (location >= 0 && location < thing.length());
}

//!
//! Adds a range to this MiGrepChar's collection of ranges
//!
void MiGrepChar::addRange(Range r)
{
	ranges.push_back(r);
}

//!
//! True if a given character is matched by this MiGrepChar
//!
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

//!
//! Prints the pattern we are building from
//!
void MiGrepCharFactory::printBuildFrom()
{
	//cout << buildFrom << endl;
}

//!
//! Initializes a new instance of MiGrepPattern by filling all matchables and setting the current object as the first
//!
MiGrepPattern::MiGrepPattern(string patternText)
{
	fillMatchables(patternText);

	if (matchables.size() == 0)
	{
		MiGrepError("Must be given pattern text");
	}
	currentIndex = 0;
}

//!
//! The current MiGrepChar matchable
//!
MiGrepChar MiGrepPattern::current()
{
	return matchables[currentIndex];
}

//!
//! True if the next matchable exists
//!
bool MiGrepPattern::nextExists()
{
	return currentIndex < (matchables.size()-1);
}

//!
//! True if the current matchable matches the given char
//!
bool MiGrepPattern::currentMatches(char me)
{
	return matchables[currentIndex].matches(me);
}

//!
//! True if the next matchable matches the given char
//!
bool MiGrepPattern::nextMatches(char me)
{
	return matchables[currentIndex+1].matches(me);
}	

//!
//! Current is now next in matchables
//!
void MiGrepPattern::moveNext()
{
	currentIndex += 1;
}

//!
//! Given a string, use a MiGrepCharFactory to construct all MiGrepChar objects
//!
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
			MiGrepError("Malformed pattern: ");
			factory.printBuildFrom();
		}
	}
}

//!
//! Sets the cardinality values of a MiGrepChar
//!
void MiGrepChar::setCardinality(CardinalityType c, int min = 0, int max = 0)
{
	card.restriction = c;
	card.minimum = min;
	card.maximum = max;
}

//!
//! True if the next character exists and is what we're looking for
//!
bool nextCharacterIs(string thing, int i, char me)
{
	return locationExists(thing, i+1) && thing[i+1] == me;
}

//!
//! True if the passed char is numeric, a comma or a space
//!
bool isNumericCommaOrSpace(char me)
{
	if ( isdigit( me ) ||
	     me == ',' || me == ' ')
	{
		return true;
	}
	return false;
}

//!
//! Given some digit as a char (0-9) return its integer value
//!
int charsIntValue(char digit)
{
	return int(digit) - 48;
}

//!
//! Does the passed character indicate a cardinality?
//!
bool isCardinalityToken(char me)
{
	return me == '+' || me == '{' ||
		me == '*';
}

//!
//! Convert a std::string to an integer
//!
int MiAToI(string thing)
{
	int result = 0;
	for (int i = 0; i < thing.length(); i += 1)
	{
		result = result*10 +  charsIntValue(thing[i]);
	}
	return result;
}

//!
//! given a char we want the literal value of, if the char is n or t return it's escaped char. Otherwise return that literal.
//!
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

//!
//! Given a MiGrepChar and a string containing a character range "[...]", parse range into the MiGrepChar
//!
int buildRanges(MiGrepChar & miGrep, string fromMe)
{
	for (int i = 1; i < fromMe.length(); i += 1)
	{
#ifdef DEBUG
		//cout << "Processing Range: " << fromMe[i] << endl;
#endif
		if (fromMe[i] == ']')
		{
			//cout << "Matches ]\n";
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

//!
//! Given a MiGrepChar and a string containing a cardinality range "{...}", parse card range into the MiGrepChar
//!
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

//!
//! Prints out basic information about a character range
//!
void Range::print()
{
	//cout << "'" << begin << "'" << "-" << "'" << end << "'";
}

//!
//! Prints out basic information about a MiGrepChar
//!
void MiGrepChar::print()
{
	//cout << "Ranges: " << endl;

	for (int i = 0; i < ranges.size(); i += 1)
	{
		//cout << "\t";
		ranges[i].print();
		//cout << endl;
	}
	//cout << "Cardinality type: " << card.restriction << endl;
	//cout << "Card start:       " << card.minimum << endl;
	//cout << "Card end:	 " << card.maximum << endl;
}

//!
//! Returns the next MiGrepChar parsed from the buildFrom string
//!
MiGrepChar MiGrepCharFactory::buildNext()
{
	MiGrepChar result = MiGrepChar();
#ifdef DEBUG
	//cout << "Processing: " << buildFrom << endl;
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
		//cout << "BUILD FROM AFTER RANGE: " << buildFrom << endl;
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
	//cout << "Generated MiGrepChar: " << endl;
	result.print();
#endif

	return result;
}

//!
//! Is there no string left to build from?
//!
bool MiGrepCharFactory::doneBuilding()
{
	return buildFrom.length() == 0;
}

//!
//! Prints an error message and exits with error status
//!
void MiGrepError(string message)
{
	//cout << "MiGrep Error:" << endl;
	//cout << message << endl;
	exit(1);
}
