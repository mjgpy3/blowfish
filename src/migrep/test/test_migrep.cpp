#include <string>
#include <iostream>
#include "migrep.h"
#include "mitest.h"
using namespace std;

int main()
{
	MiTester tester = MiTester();
	MiGrep matcher = MiGrep();

	string matchMe = "ab";
	MiGrepCharFactory factory = MiGrepCharFactory(matchMe);

	MiGrepChar a = factory.buildNext();
        tester.assertTrue(a.matches('a'), "The first MiGrepChar build by a factory out of two literals should match the first literal");
        MiGrepChar b = factory.buildNext();
	tester.assertTrue(b.matches('b'), "The second of two literals should be easily matchable");
	tester.assertFalse(a.matches('b') || b.matches('a'), "The literals should only match their values");

/*
        MiGrepCharFactory fac2 = MiGrepCharFactory(string("blowfish}"));

        while (!fac2.doneBuilding())
	{
		fac2.buildNext();
	}
*/

	tester.assertTrue(isNumericCommaOrSpace('0'), "isNumericCommaOrSpace works for some digit");
	tester.assertTrue(isNumericCommaOrSpace('9'), "isNumericCommaOrSpace works for some other digit");
	tester.assertTrue(isNumericCommaOrSpace(','), "isNumericCommaOrSpace works for ','");
	tester.assertTrue(isNumericCommaOrSpace(' '), "isNumericCommaOrSpace works for ' '");


	tester.assertTrue(matcher.isMatch("a", "a"), "Something should always match itself");
	tester.assertFalse(matcher.isMatch("b", "a"), "Some literal does not match another literal");
	tester.assertTrue(matcher.isMatch("a", "."), "Dot matches everything");
	tester.assertTrue(matcher.isMatch("aaa", "a.a"), "Dot matches anything in the middle of a string");
        tester.assertTrue(matcher.isMatch("blowfish", ".+"), "The plus quantifier allows multiple matches of the same string");
	tester.assertFalse(matcher.isMatch("blowfish", ".+a"), "Additional qualifiers (than plus) must be met also");
	tester.assertTrue(matcher.isMatch("blowfish a", ".+a"), "If those qualifiers are met, all is well");
	tester.assertTrue(matcher.isMatch("blowfish", "........"), "Some number of dots matches that same number of chars");
	tester.assertFalse(matcher.isMatch("blowfish", "."), "A statically sized pattern that is not the same length as the input, is not matched");

	tester.printResults();
	return 0;
}
