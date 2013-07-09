#ifndef MITEST
#define MITEST

#include <string>
using namespace std;

class MiTester
{
public:
	MiTester();
	void assertEqual(string a, string b);
        void printResults();
private:
	int numTestsRun;
        int numFails;
};

#endif
