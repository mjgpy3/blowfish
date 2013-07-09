#ifndef MITEST
#define MITEST

#include <string>
using namespace std;

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
