#include <iostream>
#include <map>
#include <string>
using namespace std;

int main()
{
	map<string, string> stuff;

	stuff["Michael"] = "Something";

	cout << stuff["Michael"] << endl;

	return 0;
}
