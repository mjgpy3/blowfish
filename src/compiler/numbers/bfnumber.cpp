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
#include "bfnumber.h"
using namespace std;

BfNumber::BfNumber()
{
	zeroMe();
}

BfNumber::BfNumber(string value)
{
	setFromString(value);
}

BfNumber BfNumber::add(BfNumber other)
{
	if (isNegative() == other.isNegative())
	{
		// Perform addition
		BfNumber result = BfNumber();

		if (isNegative())
		{
			result.negate();
		}

		// Normalize lengths, add, accomidate for floating overflow
		int newLen = equalizeDecimalLengths(this, &other);
		
		long long newWhole = wholePart() + other.wholePart();
		long long newDecimal = decimalPart() + other.decimalPart();

		int decLen = numLength(newDecimal);

		if (decLen > newLen)
		{
			newWhole += newDecimal / tenToThe(decLen-newLen+1);
			newDecimal = newDecimal % tenToThe(decLen-newLen+1);
		}

		result.setParts(newWhole, newDecimal);

		return result;
	}

	// Perform subtraction
	return subtract(other);
}

BfNumber BfNumber::subtract(BfNumber other)
{
	other.negate();

	if (isNegative() != other.isNegative())
	{
		// Perform subtraction
		BfNumber result = BfNumber();

		return result;
	}

	// Perform addition
	return add(other);
}

void BfNumber::setFromString(string value)
{
	zeroMe();
        long long * currentPart = &whole;

        for (int i = 0; i < value.length(); i += 1)
        {
                if (value[i] == '.')
                {
                        currentPart = &decimal;
                        continue;
                }
                (*currentPart) *= 10;
                (*currentPart) += int(value[i]) - 48;
        }

	removeEndingZeros();
}

void BfNumber::zeroMe()
{
	negative = false;
	whole = 0;
	decimal = 0;
}

void BfNumber::negate()
{
	negative = !negative;
}

bool BfNumber::isNegative()
{
	return negative;
}

long long BfNumber::wholePart()
{
	return whole;
}

long long BfNumber::decimalPart()
{
	return decimal;
}

void BfNumber::removeEndingZeros()
{
	while (decimal != 0 && decimal % 10 == 0)
	{
		decimal /= 10;
	}
}

void BfNumber::extendLengthTo(int length)
{
	int numToAppend = length - numLength(decimal);

	while (numToAppend > 0)
	{
		decimal *= 10;
		numToAppend -= 1;
	}
}

void BfNumber::setParts(long long wholePort, long long decimalPort)
{
	whole = wholePort;
	decimal = decimalPort;
}

int numLength(long long a)
{
	if (a == 0)
	{
		return 1;
	}

	return floor(log10(a)) + 1;
}

int equalizeDecimalLengths(BfNumber * a, BfNumber * b)
{
        int maxLength = max( numLength(a->decimalPart()),
                             numLength(b->decimalPart()) );

        a->extendLengthTo(maxLength);
	b->extendLengthTo(maxLength);

	return maxLength;
}

long long tenToThe(int power)
{
	long long result = 1;

	while (power > 0)
	{
		result *= 10;
		power -= 1;
	}
	return result;
}
