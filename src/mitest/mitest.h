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

#ifndef MITEST
#define MITEST

#include <string>
using namespace std;

// TODO: Improve me so that I can better be used for TDD

class MiTester
{
public:
	MiTester();
	void assertEqual(string a, string b, string message);
        void assertTrue(bool a, string message);
	void assertFalse(bool a, string message);
        void printResults();
private:
	int numTestsRun;
        int numFails;
};

#endif
