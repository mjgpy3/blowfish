#include <iostream>
using namespace std;

void foobar(int (*funct)(int), int to)
{
	cout << funct(to) << endl;
}

int plusOne(int a)
{
	return a + 1;
}

class Test
{
public:
	int (*funct)(int);
};

int main()
{
	foobar(plusOne, 7);
	Test a;
	a.funct = plusOne;

	cout << a.funct(23) << endl;

	return 0;
}
