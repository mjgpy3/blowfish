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

void given_a_bfnumber_when_we_set_it_to_something_beginning_with_zeros_then_the_extra_zeros_on_the_whole_part_are_chopped_off(MiTester & tester)
{
	// Given
	BfNumber number = BfNumber();

	// When
	number.setFromString("0032.12");

	// Then
	tester.assertTrue(number.wholePart() == 32, "Extra zeros are chopped off of the beginning of numbers");
}

void given_a_bfnumber_when_we_set_it_to_something_with_zeroes_on_the_end_of_the_decimal_part_then_the_extra_zeros_are_chopped_off(MiTester & tester)
{
	// Given
	BfNumber number = BfNumber();

	// When
	number.setFromString("13100.1200");

	// Then
	tester.assertTrue(number.decimalPart() == 12, "Extra zeros are chopped off from the end of numbers");
}

void given_a_long_long_with_three_digits_when_we_ask_for_its_length_then_it_returns_three(MiTester & tester)
{
	// Given
	long long number = 123;

	// When
	int len = numLength(number);

	// Then
	tester.assertTrue(len == 3, "We can find the length of a 3 digit number");
}

void given_a_long_long_with_one_digit_when_we_ask_for_its_length_then_it_returns_one(MiTester & tester)
{
        // Given
        long long number = 3;

        // When
        int len = numLength(number);

        // Then
        tester.assertTrue(len == 1, "We can find the length of a 1 digit number");
}

void given_a_ll_of_ten_when_we_acces_its_length_then_it_is_correct(MiTester & tester)
{
	// Given
        long long number = 1000000;

        // When
        int len = numLength(number);

        // Then
        tester.assertTrue(len == 7, "We can find the length of a 10-divisable number");
}

void given_a_zero_long_long_when_we_ask_for_its_length_then_it_returns_one(MiTester & tester)
{
	// Given
	long long number = 0;

	// When
	int len = numLength(number);

	// Then
	tester.assertTrue(len == 1, "We can find the length of 0");
}

void given_a_bfnumber_with_numlength_1_when_we_extend_it_to_length_8_then_seven_zeros_are_appended(MiTester & tester)
{
	// Given
	BfNumber number = BfNumber("3.3");

	// When
	number.extendLengthTo(8);

	// Then
	tester.assertTrue(number.decimalPart() == 30000000, "When we extend a number, a series of zeroes are attached to it");
}

void given_a_simple_bfnumber_when_we_add_another_simple_number_to_it_then_the_result_is_as_expected(MiTester & tester)
{
        // Given
        BfNumber number = BfNumber("3.3");

        // When
        BfNumber result = number.add(BfNumber("3.3"));

        // Then
        tester.assertTrue(result.decimalPart() == 6, "Adding simple, decimal");
	tester.assertTrue(result.wholePart() == 6, "Adding simple, whole");
}

void given_a_bfnumber_with_no_decimal_part_when_we_add_it_to_one_with_a_decimal_part_the_result_is_as_expected(MiTester & tester)
{
	// Given
        BfNumber number = BfNumber("92");

        // When
        BfNumber result = number.add(BfNumber("12.903"));

        // Then
        tester.assertTrue(result.decimalPart() == 903, "Adding simple, decimal");
        tester.assertTrue(result.wholePart() == 104, "Adding simple, whole");
}

void given_a_negative_bfnumber_when_we_add_another_negative_number_to_it_then_the_result_is_negative(MiTester & tester)
{
	// Given
        BfNumber number = BfNumber("92");
	number.negate();

        // When
	BfNumber other = BfNumber("324");
	other.negate();
	BfNumber result = number.add(other);

        // Then
        tester.assertTrue(result.isNegative(), "Adding negatives, result is negative");
}

void given_a_bfnumber_when_we_add_another_with_overflow_then_the_result_is_correct(MiTester & tester)
{
        // Given
        BfNumber number = BfNumber("92.5");

        // When
        BfNumber result = number.add(BfNumber("12.63"));

        // Then
        tester.assertTrue(result.wholePart() == 105, "Adding w/ overflow");
	tester.assertTrue(result.decimalPart() == 13, "adding w/ overflow");
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
	given_a_bfnumber_when_we_set_it_to_something_beginning_with_zeros_then_the_extra_zeros_on_the_whole_part_are_chopped_off(tester);
	given_a_bfnumber_when_we_set_it_to_something_with_zeroes_on_the_end_of_the_decimal_part_then_the_extra_zeros_are_chopped_off(tester);
	edge_case_bfnumbers_ending_or_beginning_with_decimals_are_parsed_properly(tester);
	given_a_zero_long_long_when_we_ask_for_its_length_then_it_returns_one(tester);
	given_a_long_long_with_three_digits_when_we_ask_for_its_length_then_it_returns_three(tester);
	given_a_long_long_with_one_digit_when_we_ask_for_its_length_then_it_returns_one(tester);
	given_a_ll_of_ten_when_we_acces_its_length_then_it_is_correct(tester);
	given_a_bfnumber_with_numlength_1_when_we_extend_it_to_length_8_then_seven_zeros_are_appended(tester);
	given_a_simple_bfnumber_when_we_add_another_simple_number_to_it_then_the_result_is_as_expected(tester);
	given_a_bfnumber_with_no_decimal_part_when_we_add_it_to_one_with_a_decimal_part_the_result_is_as_expected(tester);
	given_a_negative_bfnumber_when_we_add_another_negative_number_to_it_then_the_result_is_negative(tester);
	given_a_bfnumber_when_we_add_another_with_overflow_then_the_result_is_correct(tester);

	tester.printResults();
	return 0;
}
