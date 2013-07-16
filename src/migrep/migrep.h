#ifndef MIGREP
#define MIGREP

#include <string>
#include <vector>
using namespace std;

void MiGrepError(string message);

enum CardinalityType
{
	infinite,
	numeric
};

struct Cardinality
{
	CardinalityType restriction;
	int minimum;
	int maximum;
};

class Range
{
public:
	Range(char b, char e);
	bool includes(char me);
        void print();
private:
	char begin;
	char end;
};

class MiGrepChar
{
public:
	MiGrepChar();
	void addRange(Range r);
	void setRanges(vector<Range> rs);
	void setCardinality(CardinalityType c, int min, int max);
	void decrementCard();
	bool canStopMatching();
	bool hasInfiniteCardinality();
	bool mustStopMatching();
	bool matches(char toMatch);
	void print();
private:
	vector<Range> ranges;
        Cardinality card;
};

class MiGrepPattern
{
public:
	MiGrepPattern(string patternText);
	bool matchesText(string toMatch);

private:
	vector<MiGrepChar> matchables;
	int currentIndex;
	MiGrepChar current();
	void fillMatchables(string fromMe);
	void decrementCurrentCardinality();
	void moveNext();
	bool nextExists();
	bool canStopMatchingFrom(int index);
	bool nextMatches(char me);
	bool currentHasInfiniteCardinality();
	bool currentMatches(char me);
};

class MiGrep
{
public:
	bool isMatch(string text, string pattern);
};


class MiGrepCharFactory
{
public:
	MiGrepCharFactory(string patternText);
	MiGrepChar buildNext();
	bool doneBuilding();
	void printBuildFrom();
private:
	string buildFrom;
};

bool isNumericCommaOrSpace(char me);

#endif
