#ifndef MIGREP
#define MIGREP

#include <string>
#include <vector>
using namespace std;

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
	int mustMatch;
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
	bool matches(char toMatch);
	void print();
private:
	vector<Range> ranges;
        Cardinality card;
};

class MiGrep
{
public:
	bool isMatch(string text, string pattern);

private:
	vector<MiGrepChar> matchables;
	void fillMatchables(string fromMe);
};


class MiGrepCharFactory
{
public:
	MiGrepCharFactory(string patternText);
	MiGrepChar buildNext();
	bool doneBuilding();
	string getBuildFrom();
private:
	string buildFrom;
};

bool isNumericCommaOrSpace(char me);

#endif
