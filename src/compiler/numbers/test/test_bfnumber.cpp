/*
  Copyright (C) 2013 Michael Gilliland

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include <string>
#include "bfnumber.h"
#include "mitest.h"
using namespace std;

void given_a_bfnumber_that_has_not_been_set_to_anything_when_we_access_its_whole_and_decimal_values_then_they_are_both_zero(MiTester & tester)
{
	// Given
	BfNumber bfnumber = BfNumber();

	// When
	long long wholePart = bfnumber.wholePart();
	long long decimalPart = bfnumber.decimalPart();

	// Then
	tester.assertTrue(wholePart == 0, "Newly initialized numbers have 0 as their whole part");
	tester.assertTrue(decimalPart == 0, "Newly initialized numbers have 0 as their decimal part");
}

void given_a_bfnumber_that_is_initialized_with_a_string_representing_an_integer_when_we_access_its_whole_and_decimal_values_then_the_whole_part_is_the_strings_value_and_the_decimal_is_zero(MiTester & tester)
{
        // Given
        BfNumber bfnumber = BfNumber("42");

        // When
        long long wholePart = bfnumber.wholePart();
        long long decimalPart = bfnumber.decimalPart();

        // Then
        tester.assertTrue(wholePart == 42, "Numbers as ints have the int as their whole part");
        tester.assertTrue(decimalPart == 0, "Numbers as ints have 0 as their decimal part");
}

void given_a_bfnumber_initialized_when_a_floatlike_string_when_we_access_its_parts_then_they_are_correct(MiTester & tester)
{
	// Given
	BfNumber bfnumber = BfNumber("3.1415");

	// When
	long long wholePart = bfnumber.wholePart();
	long long decimalPart = bfnumber.decimalPart();

	// Then
	tester.assertTrue(wholePart == 3, "Floats whole parts work");
	tester.assertTrue(decimalPart == 1415, "Floats decimal parts work");
}

void given_a_non_negated_bfnumber_when_we_negate_it_then_it_is_negative(MiTester & tester)
{
	// Given
	BfNumber bfnumber = BfNumber("243.234");

	// When
	bfnumber.negate();

	// Then
	tester.assertTrue(bfnumber.isNegative(), "Numbers can be negated");
}

void edge_case_bfnumbers_ending_or_beginning_with_decimals_are_parsed_properly(MiTester & tester)
{
	// Given
        BfNumber bfnumber1 = BfNumber(".1415");
	BfNumber bfnumber2 = BfNumber("3.");

        // When
        long long wholePart1 = bfnumber1.wholePart();
        long long decimalPart1 = bfnumber1.decimalPart();
	long long wholePart2 = bfnumber2.wholePart();
        long long decimalPart2 = bfnumber2.decimalPart();


        // Then
        tester.assertTrue(wholePart1 == 0, "Decimal edge case");
        tester.assertTrue(decimalPart1 == 1415, "Decimal edge case");
	tester.assertTrue(wholePart2 == 3, "Decimal edge case");
        tester.assertTrue(decimalPart2 == 0, "Decimal edge case");
}

int main()
{
	MiTester tester = MiTester();

	given_a_bfnumber_that_has_not_been_set_to_anything_when_we_access_its_whole_and_decimal_values_then_they_are_both_zero(tester);
	given_a_bfnumber_that_is_initialized_with_a_string_representing_an_integer_when_we_access_its_whole_and_decimal_values_then_the_whole_part_is_the_strings_value_and_the_decimal_is_zero(tester);
	given_a_bfnumber_initialized_when_a_floatlike_string_when_we_access_its_parts_then_they_are_correct(tester);
	given_a_non_negated_bfnumber_when_we_negate_it_then_it_is_negative(tester);
	edge_case_bfnumbers_ending_or_beginning_with_decimals_are_parsed_properly(tester);

	tester.printResults();
	return 0;
}
