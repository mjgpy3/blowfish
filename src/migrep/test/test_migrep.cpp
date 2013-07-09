#include "migrep.h"
#include "mitest.h"
using namespace std;

int main()
{
	MiTester tester = MiTester();
	MiGrep matcher = MiGrep();

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
