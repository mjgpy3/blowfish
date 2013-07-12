#include <string>
#include <iostream>
#include "migrep.h"
#include "mitest.h"
using namespace std;

int main()
{
	MiTester tester = MiTester();
	MiGrep matcher = MiGrep();

	tester.assertTrue(isNumericCommaOrSpace('0'), "isNumericCommaOrSpace works for some digit");
	tester.assertTrue(isNumericCommaOrSpace('9'), "isNumericCommaOrSpace works for some other digit");
	tester.assertTrue(isNumericCommaOrSpace(','), "isNumericCommaOrSpace works for ','");
	tester.assertTrue(isNumericCommaOrSpace(' '), "isNumericCommaOrSpace works for ' '");

/*
	tester.assertTrue(matcher.isMatch("for", "for"), "match a simple literal token");
	tester.assertTrue(matcher.isMatch("a", "a|b"), "Simple OR should work");
	tester.assertTrue(matcher.isMatch("a", "a"), "Something should always match itself");
	tester.assertFalse(matcher.isMatch("b", "a"), "Some literal does not match another literal");
	tester.assertTrue(matcher.isMatch("a", "."), "Dot matches everything");
	tester.assertTrue(matcher.isMatch("aaa", "a.a"), "Dot matches anything in the middle of a string");
        tester.assertTrue(matcher.isMatch("blowfish", ".+"), "The plus quantifier allows multiple matches of the same string");
	tester.assertFalse(matcher.isMatch("blowfish", ".+a"), "Additional qualifiers (than plus) must be met also");
	tester.assertTrue(matcher.isMatch("blowfish a", ".+a"), "If those qualifiers are met, all is well");
	tester.assertTrue(matcher.isMatch("blowfish", "........"), "Some number of dots matches that same number of chars");
	tester.assertFalse(matcher.isMatch("blowfish", "."), "A statically sized pattern that is not the same length as the input, is not matched");
*/
	tester.printResults();
	return 0;
}
