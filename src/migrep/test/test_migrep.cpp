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

	tester.assertTrue(matcher.isMatch("a", "a|b"), "Simple OR should work");
	tester.assertTrue(matcher.isMatch("a", "a"), "Something should always match itself");
	tester.assertTrue(matcher.isMatch("for", "for"), "match a simple literal token");
	tester.assertFalse(matcher.isMatch("b", "a"), "Some literal does not match another literal");
	tester.assertTrue(matcher.isMatch("a", "."), "Dot matches everything");
	tester.assertTrue(matcher.isMatch("aaa", "a.a"), "Dot matches anything in the middle of a string");
        tester.assertTrue(matcher.isMatch("blowfish", ".+"), "The plus quantifier allows multiple matches of the same string");
	tester.assertFalse(matcher.isMatch("blowfish", ".+a"), "Additional qualifiers (than plus) must be met also");
	tester.assertTrue(matcher.isMatch("blowfish a", ".+a"), "If those qualifiers are met, all is well");
	tester.assertTrue(matcher.isMatch("blowfish", "........"), "Some number of dots matches that same number of chars");
	tester.assertFalse(matcher.isMatch("blowfish", "."), "A statically sized pattern that is not the same length as the input, is not matched");
	tester.assertTrue(matcher.isMatch("blowfish", "bl(a+foo)|(ow)fish"), "Should match where second or condition satisfies");
	tester.assertFalse(matcher.isMatch("blowfish", "bl(owf)|(i+)sh"), "OR test where none of the ors satisfy");
	tester.assertTrue(matcher.isMatch("aaaa", "a{4}"), "Exact cardinality N in {N} is hit");
	tester.assertFalse(matcher.isMatch("aaaa", "a{5}"), "If greater cardinalty, no match is hit");
	tester.assertFalse(matcher.isMatch("aaaa", "a{3}"), "If lesser cardinality, no match is hit");
	tester.assertTrue(matcher.isMatch("p5U", "[a-z][0-9][A-Z]"), "Simple range matches work");
	tester.assertTrue(matcher.isMatch("Blowfish", "[A-C][a-z]{4, 9}"), "Test ranges and cardinality ranges");
	tester.assertTrue(matcher.isMatch("blowfish", "[b-l]{2, 7}o*w+(foobar)|([fi]{2})s{1}h+"), "Complexity end-to-end test 1");
	tester.assertFalse(matcher.isMatch("blowfish", "[a-v]*"), "Ranges should not match values in said range");
	tester.assertTrue(matcher.isMatch("{{{{   |", "\\{{4} +\\|"), "Escaped characters work nicely");
	tester.assertTrue(matcher.isMatch(";(\n", "[\\;\\(\\n]{3}"), "Escaped characters in a range work alright");
	tester.assertTrue(matcher.isMatch("24.6", "[0-9]*\\.[0-9]+"), "Can match a float-like object");
	tester.assertTrue(matcher.isMatch("'a'", "'(.)|(\\\\[nt])'"), "Can match a character");
	tester.assertTrue(matcher.isMatch("]", "\\]"), "Matching a simple escaped character");
	tester.assertFalse(matcher.isMatch("", ".+"), "Empty string shouldn't be matchable with anything");

	tester.printResults();
	return 0;
}
