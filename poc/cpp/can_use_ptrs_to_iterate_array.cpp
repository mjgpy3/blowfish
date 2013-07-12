#include <iostream>
using namespace std;

int main()
{
	const int SIZE = 5;
	int a[] = {1, 2, 3, 4, 5};
	int * ptr = &a[0];

	cout << "Should print 1-5" << endl;

	for (int i = 0; i < SIZE; i += 1)
	{
		cout << *(ptr+i) << endl;
	}

	return 0;
}
