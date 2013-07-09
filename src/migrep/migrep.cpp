// Author: Michael Gilliland
#include <string>
#include <iostream>
#include "migrep.h"
using namespace std;


bool isMatch(string text, string pattern)
{
	if (text.compare(pattern) == 0)
	{
		return true;
	}
	return false;
}
