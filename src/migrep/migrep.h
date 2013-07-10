#ifndef MIGREP
#define MIGREP

#include <string>
#include <vector>
using namespace std;

class Range
{
public:
	Range(char b, char e);
	bool includes(char me);
private:
	char begin;
	char end;
};

class MiGrepChar
{
public:
	MiGrepChar();
	bool matches(char toMatch);
private:
	vector<Range> ranges;
};

class MiGrep
{
public:
	bool isMatch(string text, string pattern);

private:
	vector<MiGrepChar> patternChars;
};


class MiGrepCharFactory
{
public:
	MiGrepCharFactory(string patternText);
	MiGrepChar buildNext();
	bool doneBuilding();
private:
	string buildFrom;
};

#endif
