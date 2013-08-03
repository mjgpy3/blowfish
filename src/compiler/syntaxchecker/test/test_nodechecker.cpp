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

#include "bfnodechecker.h"
#include "mitest.h"
#include "bfnodes.h"
using namespace std;

void children_of_a_node_can_be_identified_exactly_as_they_are_by_type(MiTester & tester)
{
	// Given
        BfRoot * aRoot = new BfRoot();
        NodeIdentifier ids[] = { id_plus, id_minus, id_concat };

        // When
        (*aRoot).appendChild(new BfPlus());
        (*aRoot).appendChild(new BfMinus());
        (*aRoot).appendChild(new BfConcat());

        // Then
        tester.assertTrue(childrenAreExactly(aRoot, ids), "Attaching a few operator nodes are recognizable as being what they are (by id)");
}

void if_all_children_dont_exactly_match_then_identification_is_false(MiTester & tester)
{
	// Given
	BfRoot * aRoot = new BfRoot();
	NodeIdentifier ids[] = { id_plus, id_minus };

	// When
	(*aRoot).appendChild(new BfPlus());
	(*aRoot).appendChild(new BfMinus());
	(*aRoot).appendChild(new BfMultiply());

	// Then
	tester.assertFalse(childrenAreExactly(aRoot, ids), "Children must match exactly");
}

void operator_nodes_can_be_identified_as_such(MiTester & tester)
{
        // Given
        BfRoot * aRoot = new BfRoot();
        NodeIdentifier ids[] = { id_plus, id_minus, id_concat };

        // When
        (*aRoot).appendChild(new BfPlus());
        (*aRoot).appendChild(new BfMinus());
        (*aRoot).appendChild(new BfConcat());

        // Then
        for (int i = 0; i < (*aRoot).numChildren(); i += 1)
        {
                tester.assertTrue(isOperator((*aRoot).child(i)), "Operator nodes are recognizable");
        }
}

void literals_can_be_identified_as_such(MiTester & tester)
{
        // Given
        BfRoot * aRoot = new BfRoot();

        // When
        (*aRoot).appendChild(new BfString("Something"));
        (*aRoot).appendChild(new BfInteger("1"));
        (*aRoot).appendChild(new BfFloat("1.0"));

        // Then
        for (int i = 0; i < (*aRoot).numChildren(); i += 1)
        {
                tester.assertTrue(isLiteral((*aRoot).child(i)), "Literal nodes are recognizable");
        }
}

void can_identify_nodes_that_indicate_a_scope(MiTester & tester)
{
        // Given
        BfRoot * aRoot = new BfRoot();

        // When
        (*aRoot).appendChild(new BfClassDef());
        (*aRoot).appendChild(new BfModuleDef());
        (*aRoot).appendChild(new BfMethodDef());
        (*aRoot).appendChild(new BfIf());
        (*aRoot).appendChild(new BfElseIf());
        (*aRoot).appendChild(new BfElse());
	(*aRoot).appendChild(new BfForLoop());
	(*aRoot).appendChild(new BfEnumLoop());

        // Then
        for (int i = 0; i < (*aRoot).numChildren(); i += 1)
        {
                tester.assertTrue(impliesScope((*aRoot).child(i)), "Definitions and statements that come before blocks imply scope");
        }
}

int main()
{
        MiTester tester = MiTester();

	children_of_a_node_can_be_identified_exactly_as_they_are_by_type(tester);
	if_all_children_dont_exactly_match_then_identification_is_false(tester);
	operator_nodes_can_be_identified_as_such(tester);
	literals_can_be_identified_as_such(tester);
	can_identify_nodes_that_indicate_a_scope(tester);

	tester.printResults();
	return 0;
}
