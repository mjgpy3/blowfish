// Author: Michael Gilliland
#include <string>
#include <iostream>
#include "migrep.h"
using namespace std;


bool MiGrep::isMatch(string text, string pattern)
{
	// TODO: Keep current, look for current and next

	if (pattern.compare(".+") == 0)
	{
		return true;
	}

	for (int i = 0; i < text.length(); i += 1)
	{
		if (!(pattern[i] == text[i] || pattern[i] == '.'))
		{
			return false;
		}
	}

	return true;
}
