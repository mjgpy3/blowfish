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


#include <iostream>
#include <string>
#include "mitest.h"
using namespace std;

MiTester::MiTester()
{
	numTestsRun = 0;
	numFails = 0;
}

void MiTester::assertEqual(string a, string b, string message)
{
	numTestsRun += 1;

	if (a.compare(b) == 0)
	{
		cout << ".";
	}
	else
	{
		cout << "E";
                cout << endl;
		cout << message << endl;
		numFails += 1;
	}
}

void MiTester::assertFalse(bool a, string message)
{
	MiTester::assertTrue(!a, message);
}

void MiTester::assertTrue(bool a, string message)
{
	numTestsRun += 1;

	if (a)
	{
		cout << ".";
	}
	else
	{
		cout << "E";
		cout << endl;
		cout << message << endl;
		numFails += 1;
	}
}

void MiTester::printResults()
{
        cout << endl;
	cout << "Tests run: " << numTestsRun << endl;
	cout << "Success:   " << numTestsRun - numFails << endl;
        cout << "Fail:      " << numFails << endl;
}
