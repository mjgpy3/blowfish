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

#include <cmath>
#include <iostream>
#include <string>
#include "bfliteraltypes.h"
#include "bfnumber.h"
#include "mitest.h"
using namespace std;

bool withinEpsilon(double a, double b, double eps)
{
	return eps >= abs(a - b);
}

void given_a_bfinteger_when_we_set_it_from_a_string_then_that_same_value_can_be_retrieved(MiTester & tester)
{
	// Given
	BfIntegerNumber intNum = BfIntegerNumber();

	// When
	intNum.setFromString("42");

	// Then
	tester.assertTrue(intNum.getInt() == 42, "We can set and get an integer");
}

void given_a_bffloat_when_we_set_it_from_a_string_then_that_same_value_can_be_retrieved(MiTester & tester)
{
	// Given
	BfFloatNumber floatNum = BfFloatNumber();

	// When
	floatNum.setFromString("123.456");

	// Then
	tester.assertTrue(floatNum.getFloat() == 123.456, "We can set and get a float");
}

void given_a_bfinteger_when_we_negate_it_then_its_value_is_negative(MiTester & tester)
{
	// Given
	BfIntegerNumber intNum = BfIntegerNumber("42");

	// When
	BfNumber * negatedNum = negateNum(&intNum);

	// Then
	tester.assertTrue(negatedNum->getInt() == -42, "We can negate an integer");
}

void given_a_bffloat_when_we_negate_it_then_its_value_is_negative(MiTester & tester)
{
        // Given
        BfFloatNumber floatNum = BfFloatNumber("42.92");

        // When
        BfNumber * negatedNum = negateNum(&floatNum);

        // Then
        tester.assertTrue(negatedNum->getFloat() == -42.92, "We can negate a float");
}

void given_two_bfintegers_when_we_add_them_then_their_result_is_the_sum_of_their_values(MiTester & tester)
{
	// Given
	BfIntegerNumber numOne = BfIntegerNumber("42");
	BfIntegerNumber numTwo = BfIntegerNumber("35");

	// When
	BfNumber * result = add(&numOne, &numTwo);

	// Then
	tester.assertTrue(numOne.getInt() + numTwo.getInt() == result->getInt(), "We can add two integers");
}

void given_two_bffloats_when_we_add_them_then_their_result_is_the_sum_of_their_values(MiTester & tester)
{
        // Given
        BfFloatNumber numOne = BfFloatNumber("42.98");
        BfFloatNumber numTwo = BfFloatNumber("3.105");

        // When
        BfNumber * result = add(&numOne, &numTwo);

        // Then
        tester.assertTrue(withinEpsilon(46.085, result->getFloat(), 0.00000000000001), "We can add two floats");
}

void given_a_bfinteger_and_a_bffloat_when_we_add_them_then_the_result_is_a_bffloat(MiTester & tester)
{
	// Given
	BfFloatNumber numOne = BfFloatNumber("0.0");
	BfIntegerNumber numTwo = BfIntegerNumber("0");

	// When
	BfNumber * result = add(&numOne, &numTwo);

	// Then
	tester.assertTrue(result->getTypeId() == type_float, "When we do some operation with mixed ints and floats, the result is a float");
}

void given_two_bfintegers_when_we_subtract_them_then_their_result_is_the_difference_of_their_values(MiTester & tester)
{
	// Given
	BfIntegerNumber numOne = BfIntegerNumber("42");
        BfIntegerNumber numTwo = BfIntegerNumber("35");

        // When
        BfNumber * result = subtract(&numOne, &numTwo);

        // Then
        tester.assertTrue(numOne.getInt() - numTwo.getInt() == result->getInt(), "We can subtract two integers");
}

void given_two_bffloats_when_we_subtract_them_then_their_result_is_the_difference_of_their_values(MiTester & tester)
{
        // Given
        BfFloatNumber numTwo = BfFloatNumber("42.98");
        BfFloatNumber numOne = BfFloatNumber("3.105");

        // When
        BfNumber * result = subtract(&numOne, &numTwo);

        // Then
        tester.assertTrue(withinEpsilon(-39.875, result->getFloat(), 0.00000000000001), "We can subtract two floats");
}

void given_two_bfintegers_when_we_multiply_them_then_their_result_is_the_product_of_their_values(MiTester & tester)
{
        // Given
        BfIntegerNumber numOne = BfIntegerNumber("42");
        BfIntegerNumber numTwo = BfIntegerNumber("35");

        // When
        BfNumber * result = multiply(&numOne, &numTwo);

        // Then
        tester.assertTrue(numOne.getInt() * numTwo.getInt() == result->getInt(), "We can multiply two integers");
}

void given_two_bffloats_when_we_multiply_them_then_their_result_is_the_product_of_their_values(MiTester & tester)
{
        // Given
        BfFloatNumber numTwo = BfFloatNumber("42.98");
        BfFloatNumber numOne = BfFloatNumber("3.105");

        // When
        BfNumber * result = multiply(&numOne, &numTwo);

        // Then
        tester.assertTrue(withinEpsilon(133.4529, result->getFloat(), 0.00000000000001), "We can multiply two floats");
}

void given_two_bfintegers_when_we_divide_them_then_their_result_is_the_quotent_of_their_values(MiTester & tester)
{
        // Given
        BfIntegerNumber numOne = BfIntegerNumber("9");
        BfIntegerNumber numTwo = BfIntegerNumber("2");

        // When
        BfNumber * result = divide(&numOne, &numTwo);

        // Then
        tester.assertTrue(4 == result->getInt(), "We can divide two integers");
}

void given_two_bffloats_when_we_divide_them_then_their_result_is_the_quotent_of_their_values(MiTester & tester)
{
        // Given
        BfFloatNumber numOne = BfFloatNumber("42.96");
        BfFloatNumber numTwo = BfFloatNumber("12.0");

        // When
        BfNumber * result = divide(&numOne, &numTwo);

        // Then
        tester.assertTrue(withinEpsilon(3.58, result->getFloat(), 0.00000000000001), "We can divide two floats");
}

void given_two_bfintegers_when_we_modulus_them_then_their_result_is_the_modulus_of_their_values(MiTester & tester)
{
        // Given
        BfIntegerNumber numOne = BfIntegerNumber("14");
        BfIntegerNumber numTwo = BfIntegerNumber("5");

        // When
        BfIntegerNumber * result = mod(numOne, numTwo);

        // Then
        tester.assertTrue(numOne.getInt() % numTwo.getInt() == result->getInt(), "We can modulus two integers");
}

void given_two_bfintegers_when_we_exponentiate_them_then_their_result_is_the_exponentiation_of_thier_values(MiTester & tester)
{
        // Given
        BfIntegerNumber numOne = BfIntegerNumber("5");
        BfIntegerNumber numTwo = BfIntegerNumber("3");

        // When
        BfNumber * result = power(&numOne, &numTwo);
        
        // Then
        tester.assertTrue(125 == result->getInt(), "We can exponentiate two integers");
}

void given_two_bffloats_when_we_exponentiate_them_then_their_result_is_the_exponentiation_of_their_values(MiTester & tester)
{
        // Given
        BfFloatNumber numOne = BfFloatNumber("42.96");
        BfFloatNumber numTwo = BfFloatNumber("4.9");

        // When
        BfNumber * result = power(&numOne, &numTwo);

        // Then
        tester.assertTrue(withinEpsilon(100465034.14627065, result->getFloat(), 0.00000000000001), "We can exponentiate two floats");
}

int main()
{
	MiTester tester = MiTester();

	given_a_bfinteger_when_we_set_it_from_a_string_then_that_same_value_can_be_retrieved(tester);
	given_a_bfinteger_when_we_negate_it_then_its_value_is_negative(tester);
	given_two_bfintegers_when_we_add_them_then_their_result_is_the_sum_of_their_values(tester);
	given_two_bfintegers_when_we_subtract_them_then_their_result_is_the_difference_of_their_values(tester);
	given_two_bfintegers_when_we_multiply_them_then_their_result_is_the_product_of_their_values(tester);
	given_two_bfintegers_when_we_divide_them_then_their_result_is_the_quotent_of_their_values(tester);
	given_two_bfintegers_when_we_modulus_them_then_their_result_is_the_modulus_of_their_values(tester);
	given_two_bfintegers_when_we_exponentiate_them_then_their_result_is_the_exponentiation_of_thier_values(tester);

	given_a_bffloat_when_we_set_it_from_a_string_then_that_same_value_can_be_retrieved(tester);
	given_a_bffloat_when_we_negate_it_then_its_value_is_negative(tester);
	given_two_bffloats_when_we_add_them_then_their_result_is_the_sum_of_their_values(tester);
	given_two_bffloats_when_we_subtract_them_then_their_result_is_the_difference_of_their_values(tester);
	given_two_bffloats_when_we_multiply_them_then_their_result_is_the_product_of_their_values(tester);
	given_two_bffloats_when_we_divide_them_then_their_result_is_the_quotent_of_their_values(tester);
	given_two_bffloats_when_we_exponentiate_them_then_their_result_is_the_exponentiation_of_their_values(tester);

	given_a_bfinteger_and_a_bffloat_when_we_add_them_then_the_result_is_a_bffloat(tester);

	tester.printResults();
	return 0;
}
