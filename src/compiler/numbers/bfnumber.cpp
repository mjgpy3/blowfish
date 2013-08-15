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
using namespace std;

BfNumber::BfNumber()
{
	zeroMe();
}

BfNumber::BfNumber(string value)
{
	setFromString(value);
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
