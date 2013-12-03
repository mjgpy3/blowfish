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

int main()
{
	foobar(plusOne, 7);

	return 0;
}
