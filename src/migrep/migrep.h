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
