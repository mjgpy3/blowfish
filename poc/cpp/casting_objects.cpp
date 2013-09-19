#include <iostream>
using namespace std;

class A
{
};

class B : public A
{
};

int main()
{
	A * a = new B();
	B * b = dynamic_cast<B*>(a);

	return 0;
}
