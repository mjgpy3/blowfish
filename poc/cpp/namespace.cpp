#include <iostream>
using namespace std;

namespace Foo
{
	int a = 6;
};

int main()
{
	cout << Foo::a << endl;
	Foo::a = 787878;
	cout << Foo::a << endl;
	return 0;
}
