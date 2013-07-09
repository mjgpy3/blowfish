#include <iostream>
#include <string>
#include "mitest.h"
using namespace std;

MiTester::MiTester()
{
	numTestsRun = 0;
	numFails = 0;
}

void MiTester::assertEqual(string a, string b)
{
	numTestsRun += 1;

	if (a.compare(b) == 0)
	{
		cout << ".";
	}
	else
	{
		cout << "E";
		numFails += 1;
	}
}

void MiTester::assertFalse(bool a)
{
	MiTester::assertTrue(!a);
}

void MiTester::assertTrue(bool a)
{
	numTestsRun += 1;

	if (a)
	{
		cout << ".";
	}
	else
	{
		cout << "E";
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
