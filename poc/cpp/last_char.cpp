#include <iostream>
#include <string>
using namespace std;

int main()
{
	string name = "Michael";

	cout << *name.rbegin() << endl;
	cout << name.substr(0, name.length()-1);

	return 0;
}
