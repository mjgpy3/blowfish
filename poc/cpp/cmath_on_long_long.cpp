#include <cmath>
#include <iostream>
using namespace std;

int main()
{
	long long a = 10000001000000000;
	long long b = 123;
	cout << "Sqrt:  " << sqrt(a) << endl;
	cout << "Log10: " << log10(a) << endl;
	cout << "Ceil(Log10): " << ceil(log10(b)) << endl;
	return 0;
}
