#include <string>
#include <iostream>
using namespace std;

int main()
{
	string a = "''";
	cout << a.substr(1, a.length()-2) << endl;
	return 0;
}
