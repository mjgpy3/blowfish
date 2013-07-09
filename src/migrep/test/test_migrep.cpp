#include "migrep.h"
#include "mitest.h"
using namespace std;

int main()
{
	MiTester tester = MiTester();

	tester.assertTrue(isMatch("a", "a"));

	tester.printResults();
	return 0;
}
