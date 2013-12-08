#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
	ostringstream ss;
	long long a = 53165132;

	ss << a;

	cout << ss.str() + " ans" << endl;

	return 0;
}
