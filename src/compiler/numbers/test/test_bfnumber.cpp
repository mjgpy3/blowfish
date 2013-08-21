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

void given_a_bfinteger_when_we_set_it_from_a_string_then_that_same_value_can_be_retrieved(MiTester & tester)
{
	// Given
	BfIntegerNumber intNum = BfIntegerNumber();

	// When
	intNum.setFromString("42");

	// Then
	tester.assertTrue(intNum.getInt() == 42, "We can set and get an integer");
}

void given_a_bfinteger_when_we_negate_it_then_its_value_is_negative(MiTester & tester)
{
	// Given
	BfIntegerNumber intNum = BfIntegerNumber("42");

	// When
	BfIntegerNumber * negatedNum = negateNum(intNum);

	// Then
	tester.assertTrue(negatedNum->getInt() == -intNum.getInt(), "We can negate an integer");
}

void given_two_bfintegers_when_we_add_them_then_their_result_is_the_sum_of_their_values(MiTester & tester)
{
	// Given
	BfIntegerNumber numOne = BfIntegerNumber("42");
	BfIntegerNumber numTwo = BfIntegerNumber("35");

	// When
	BfIntegerNumber * result = add(numOne, numTwo);

	// Then
	tester.assertTrue(numOne.getInt() + numTwo.getInt() == result->getInt(), "We can add two integers");
}

void given_two_bfintegers_when_we_subtract_them_then_their_result_is_the_difference_of_their_values(MiTester & tester)
{
	// Given
	BfIntegerNumber numOne = BfIntegerNumber("42");
        BfIntegerNumber numTwo = BfIntegerNumber("35");

        // When
        BfIntegerNumber * result = subtract(numOne, numTwo);

        // Then
        tester.assertTrue(numOne.getInt() - numTwo.getInt() == result->getInt(), "We can subtract two integers");
}

void given_two_bfintegers_when_we_multiply_them_then_their_result_is_the_product_of_their_values(MiTester & tester)
{
        // Given
        BfIntegerNumber numOne = BfIntegerNumber("42");
        BfIntegerNumber numTwo = BfIntegerNumber("35");

        // When
        BfIntegerNumber * result = multiply(numOne, numTwo);

        // Then
        tester.assertTrue(numOne.getInt() * numTwo.getInt() == result->getInt(), "We can multiply two integers");
}

int main()
{
	MiTester tester = MiTester();

	given_a_bfinteger_when_we_set_it_from_a_string_then_that_same_value_can_be_retrieved(tester);
	given_a_bfinteger_when_we_negate_it_then_its_value_is_negative(tester);
	given_two_bfintegers_when_we_add_them_then_their_result_is_the_sum_of_their_values(tester);
	given_two_bfintegers_when_we_subtract_them_then_their_result_is_the_difference_of_their_values(tester);
	given_two_bfintegers_when_we_multiply_them_then_their_result_is_the_product_of_their_values(tester);

	tester.printResults();
	return 0;
}
