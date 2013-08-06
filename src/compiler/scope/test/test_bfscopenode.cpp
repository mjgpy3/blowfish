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

#include "bfscopenode.h"
#include "mitest.h"
using namespace std;

void given_a_scope_node_when_we_have_done_nothing_to_that_node_then_its_number_of_children_is_zero(MiTester & tester)
{
	// Given
	BfScopeNode * node = new BfScopeNode();

	// When

	// Then
	tester.assertTrue((*node).numChildren() == 0, "A node with no children should have 0 children");
}

void given_an_empty_scope_node_when_we_append_a_pointer_to_another_scope_node_then_that_node_should_have_one_child(MiTester & tester)
{
	// Given
	BfScopeNode * node = new BfScopeNode();

	// When
	(*node).appendChild(new BfScopeNode());

	// Then
	tester.assertTrue((*node).numChildren() == 1, "A node with another node appended to it has 1 child");
}

void given_an_empty_scope_node_when_we_append_a_pointer_to_another_scope_node_then_the_append_nodes_parent_should_be_the_original_node(MiTester & tester)
{
	// Given
	BfScopeNode * node = new BfScopeNode();
	BfScopeNode * anotherNode = new BfScopeNode();

	// When
	(*node).appendChild(anotherNode);

	// Then
	tester.assertTrue((*anotherNode).parentIs(node), "An appended node's parent is the node that it was appended to");
}

int main()
{
	MiTester tester = MiTester();

	given_a_scope_node_when_we_have_done_nothing_to_that_node_then_its_number_of_children_is_zero(tester);
	given_an_empty_scope_node_when_we_append_a_pointer_to_another_scope_node_then_that_node_should_have_one_child(tester);
	given_an_empty_scope_node_when_we_append_a_pointer_to_another_scope_node_then_the_append_nodes_parent_should_be_the_original_node(tester);

	tester.printResults();

	return 0;
}
