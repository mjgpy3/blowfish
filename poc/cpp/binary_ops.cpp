#include <iostream>
using namespace std;

int main()
{
	for (int a = 0; a < 2; a += 1)
	{
		for (int b = 0; b < 2; b += 1)
		{
			bool result = !(bool(a)^bool(b));
			cout << "a^b = " << a << "^" << b  << " = " << result << endl; 
		}
	}

	return 0;
}
