#include <iostream>
using namespace std;

int main()
{
	int * ptr = NULL;
	int a = 5;

	if (ptr == NULL)
	{
		cout << "Pointer is null as it should be" << endl;
	}

	ptr = &a;

	if (*ptr == 5)
	{
		cout << "Pointer is 5 as it should be" << endl;
	}

	ptr = 0;

        if (ptr == NULL)
        {
                cout << "Pointer is null as it should be" << endl;
        }


	return 0;
}
