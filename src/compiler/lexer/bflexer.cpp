#include <regex>

#ifndef BLOWFISH_TOKENS
#define BLOWFISH_TOKENS
typedef struct
{
	char* name;
	char* match;
	bool isKeyword;
	bool savesText;
	bool isIgnored;
} Token;
#endif
