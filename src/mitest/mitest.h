#ifndef MITEST
#define MITEST

#include <string>
using namespace std;

class MiTester
{
public:
	MiTester();
	void assertEqual(string a, string b);
        void assertTrue(bool a);
	void assertFalse(bool a);
        void printResults();
private:
	int numTestsRun;
        int numFails;
};

#endif
