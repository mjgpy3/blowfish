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
#include <sstream>
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

long long BfFloatNumber::getInt()
{
	return (long long)underFloat;
}

double BfIntegerNumber::getFloat()
{
	return double(underInt);
}

double BfFloatNumber::getFloat()
{
	return underFloat;
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

string BfFloatNumber::toString()
{
	ostringstream ss;
	ss << underFloat;
	return ss.str();
}

string BfIntegerNumber::toString()
{
	ostringstream ss;
	ss << underInt;
	return ss.str();
}

void BfFloatNumber::setFromString(string value)
{
	zeroMe();
	bool decimalFound = false;
	int tens = 10;

	for (int i = 0; i < value.length(); i += 1)
	{
		if (value[i] == '.')
		{
			decimalFound = true;
			continue;
		}

		if (!decimalFound)
		{
			underFloat *= 10;
			underFloat += double(int(value[i]) - 48);
		}
		else
		{
			underFloat += double(int(value[i]) - 48)/tens;
			tens *= 10;
		}
	}
}

BfNumber * negateNum(BfNumber * num)
{
	BfNumber * result;
	
	if (num->getTypeId() == type_int)
	{
       		result = new BfIntegerNumber();
		result->underInt = -num->getInt();
	}
	else
	{
		result = new BfFloatNumber();
		result->underFloat = -num->getFloat();
	}

       	return result;
}

BfNumber * add(BfNumber * num1, BfNumber * num2)
{
	BfNumber * result;

	if (num1->getTypeId() == type_float || num1->getTypeId() == type_float)
	{
		result = new BfFloatNumber();
		result->underFloat = num1->getFloat() + num2->getFloat();
	}
	else
	{
		result = new BfIntegerNumber();
		result->underInt = num1->getInt() + num2->getInt();
	}

	return result;
}

BfNumber * subtract(BfNumber * num1, BfNumber * num2)
{
        BfNumber * result;

        if (num1->getTypeId() == type_float || num1->getTypeId() == type_float)
        {
                result = new BfFloatNumber();
                result->underFloat = num1->getFloat() - num2->getFloat();
        }
        else
        {
                result = new BfIntegerNumber();
                result->underInt = num1->getInt() - num2->getInt();
        }

        return result;
}

BfNumber * multiply(BfNumber * num1, BfNumber * num2)
{
        BfNumber * result;

        if (num1->getTypeId() == type_float || num1->getTypeId() == type_float)
        {
                result = new BfFloatNumber();
                result->underFloat = num1->getFloat() * num2->getFloat();
        }
        else
        {
                result = new BfIntegerNumber();
                result->underInt = num1->getInt() * num2->getInt();
        }

        return result;
}

BfNumber * divide(BfNumber * num1, BfNumber * num2)
{
        BfNumber * result;

        if (num1->getTypeId() == type_float || num1->getTypeId() == type_float)
        {
                result = new BfFloatNumber();
                result->underFloat = num1->getFloat() / num2->getFloat();
        }
        else
        {
                result = new BfIntegerNumber();
                result->underInt = num1->getInt() / num2->getInt();
        }

        return result;
}

BfNumber * mod(BfNumber * num1, BfNumber * num2)
{
	long long resultVal = num1->getInt() % num2->getInt();
	BfIntegerNumber * result = new BfIntegerNumber();
        result->underInt = resultVal;

        return result;
}

BfNumber * power(BfNumber * num1, BfNumber * num2)
{
	BfNumber * result;

        if (num1->getTypeId() == type_float || num1->getTypeId() == type_float)
        {
                result = new BfFloatNumber();
                result->underFloat = pow(num1->getFloat(),  num2->getFloat());
        }
        else
        {
                result = new BfIntegerNumber();
                result->underInt = pow(num1->getInt(), num2->getInt());
        }
        
        return result;
}

BfIntegerNumber * power(BfIntegerNumber num1, BfIntegerNumber num2)
{
	long long resultVal = pow(num1.getInt(), num2.getInt());
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
