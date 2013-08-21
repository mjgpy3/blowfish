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

#ifndef BLOWFISH_NUMBER
#define BLOWFISH_NUMBER

#include <string>
#include "bfliteraltypes.h"
using namespace std;

class BfNumber
{
public:
	BfNumber();
	BfNumber(string value);
	virtual void setFromString(string value) = 0;
	virtual long long getInt() = 0;
	virtual double getFloat() = 0;
	void setNumType(LiteralType type);
	double underFloat;
	long long underInt;
	void zeroMe();
	LiteralType getTypeId()
	{
		return numType;
	}

private:
	LiteralType numType;
};

class BfIntegerNumber : public BfNumber
{
public:
	BfIntegerNumber() : BfNumber()
	{
		setNumType(type_int);
	}

	BfIntegerNumber(string value) : BfNumber()
	{
		setFromString(value);
		setNumType(type_int);
	}

	long long getInt();
	double getFloat();
	void setFromString(string value);
};

class BfFloatNumber : public BfNumber
{
public:
	BfFloatNumber() : BfNumber()
	{
		setNumType(type_float);
	}

	long long getInt();
	double getFloat();
	void setFromString(string value);
};

int numLength(long long a);

BfIntegerNumber * negateNum(BfIntegerNumber num);
BfIntegerNumber * add(BfIntegerNumber num1, BfIntegerNumber num2);
BfIntegerNumber * subtract(BfIntegerNumber num1, BfIntegerNumber num2);
BfIntegerNumber * multiply(BfIntegerNumber num1, BfIntegerNumber num2);


#endif
