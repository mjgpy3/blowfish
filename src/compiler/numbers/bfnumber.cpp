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
using namespace std;

BfNumber::BfNumber()
{
}

void BfNumber::setNumType(LiteralType type)
{
	numType = type;
}

void BfNumber::zeroMe()
{
	underFloat = 0.0;
	underInt = 0;
}

long long BfIntegerNumber::getInt()
{
	return underInt;
}

double BfIntegerNumber::getFloat()
{
	return double(underInt);
}

void BfIntegerNumber::setFromString(string value)
{
        zeroMe();

        for (int i = 0; i < value.length(); i += 1)
        {
                underInt *= 10;
                underInt += int(value[i]) - 48;
        }
}

BfIntegerNumber * negateNum(BfIntegerNumber num)
{
	long long resultVal = - num.getInt();
	BfIntegerNumber * result = new BfIntegerNumber();
	result->underInt = resultVal;

	return result;
}

BfIntegerNumber * add(BfIntegerNumber num1, BfIntegerNumber num2)
{
	long long resultVal = num1.getInt() + num2.getInt();
	BfIntegerNumber * result = new BfIntegerNumber();
	result->underInt = resultVal;

	return result;
}

BfIntegerNumber * subtract(BfIntegerNumber num1, BfIntegerNumber num2)
{
	long long resultVal = num1.getInt() - num2.getInt();
        BfIntegerNumber * result = new BfIntegerNumber();
        result->underInt = resultVal;

        return result;
}

BfIntegerNumber * multiply(BfIntegerNumber num1, BfIntegerNumber num2)
{
        long long resultVal = num1.getInt() * num2.getInt();
        BfIntegerNumber * result = new BfIntegerNumber();
        result->underInt = resultVal;

        return result;
}

int numLength(long long a)
{
	if (a == 0)
	{
		return 1;
	}

	return floor(log10(a)) + 1;
}
