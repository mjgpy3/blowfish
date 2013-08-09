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

#include "bfnodefactory.h"
#include "bfnodes.h"
#include "bftokennames.h"
#include "mitest.h"
using namespace std;

void given_a_plus_token_name_when_it_is_given_to_the_operator_node_factory_then_a_BfPlus_node_is_built(MiTester & tester)
{
	// Given
	TokenName tok = t_op_plus;

	// When
	BfNode * node = BfOperatorNodeFactory(tok);

	// Then
	tester.assertTrue(node->getTypeId() == t_op_plus, "Op factory generates plus node");
}

void given_a_minus_token_name_when_it_is_given_to_the_operator_node_factory_then_a_BfMinus_node_is_built(MiTester & tester)
{
        // Given
        TokenName tok = t_op_minus;

        // When
        BfNode * node = BfOperatorNodeFactory(tok);

        // Then
        tester.assertTrue(node->getTypeId() == t_op_minus, "Op factory generates minus node");
}

void given_an_or_token_name_when_it_is_given_to_the_operator_node_factory_then_a_BfOr_node_is_built(MiTester & tester)
{
        // Given
        TokenName tok = t_kwd_or;
        
        // When
        BfNode * node = BfOperatorNodeFactory(tok);

        // Then
        tester.assertTrue(node->getTypeId() == t_kwd_or, "Op factory generates or node");
}

void given_an_and_token_name_when_it_is_given_to_the_operator_node_factory_then_a_BfAnd_node_is_built(MiTester & tester)
{
        // Given
        TokenName tok = t_kwd_and;
        
        // When
        BfNode * node = BfOperatorNodeFactory(tok);
        
        // Then
        tester.assertTrue(node->getTypeId() == t_kwd_and, "Op factory generates and node");
}

void given_a_greater_than_token_name_when_it_is_given_to_the_operator_node_factory_then_a_BfGreaterThan_node_is_built(MiTester & tester)
{
        // Given
        TokenName tok = t_op_gt;

        // When
        BfNode * node = BfOperatorNodeFactory(tok);

        // Then
        tester.assertTrue(node->getTypeId() == t_op_gt, "Op factory generates greater-than node");
}

void given_a_less_than_token_name_when_it_is_given_to_the_operator_node_factory_then_a_BfLessThan_node_is_built(MiTester & tester)
{
        // Given
        TokenName tok = t_op_lt;
        
        // When
        BfNode * node = BfOperatorNodeFactory(tok);
        
        // Then
        tester.assertTrue(node->getTypeId() == t_op_lt, "Op factory generates less-than node");
}

void given_a_greater_than_or_equal_token_name_when_it_is_given_to_the_operator_node_factory_then_a_BfGreaterThanOrEqual_node_is_built(MiTester & tester)
{
        // Given
        TokenName tok = t_op_geq;
        
        // When
        BfNode * node = BfOperatorNodeFactory(tok);
        
        // Then
        tester.assertTrue(node->getTypeId() == t_op_geq, "Op factory generates greater than or equal node");
}

void given_a_less_than_or_equal_token_name_when_it_is_given_to_the_operator_node_factory_then_a_BfLessThanOrEqual_node_is_built(MiTester & tester)
{
        // Given
        TokenName tok = t_op_leq;
        
        // When
        BfNode * node = BfOperatorNodeFactory(tok);
        
        // Then
        tester.assertTrue(node->getTypeId() == t_op_leq, "Op factory generates less than or equal node");
}

void given_an_equal_token_name_when_it_is_given_to_the_operator_node_factory_then_a_BfEqual_node_is_built(MiTester & tester)
{
        // Given
        TokenName tok = t_op_eq;
        
        // When
        BfNode * node = BfOperatorNodeFactory(tok);
        
        // Then
        tester.assertTrue(node->getTypeId() == t_op_eq, "Op factory generates equal node");
} 

void given_a_not_equal_token_name_when_it_is_given_to_the_operator_node_factory_then_a_BfNotEqual_node_is_built(MiTester & tester)
{
        // Given
        TokenName tok = t_op_noteq;

        // When
        BfNode * node = BfOperatorNodeFactory(tok);

        // Then
        tester.assertTrue(node->getTypeId() == t_op_noteq, "Op factory generates not equal node");
}

void given_a_concat_token_name_when_it_is_given_to_the_operator_node_factory_then_a_BfConcat_node_is_built(MiTester & tester)
{
        // Given
        TokenName tok = t_op_concat;

        // When
        BfNode * node = BfOperatorNodeFactory(tok);

        // Then
        tester.assertTrue(node->getTypeId() == t_op_concat, "Op factory generates concat node");
}

void given_a_modulus_token_name_when_it_is_given_to_the_operator_node_factory_then_a_BfModulus_node_is_built(MiTester & tester)
{
        // Given
        TokenName tok = t_op_modulus;

        // When
        BfNode * node = BfOperatorNodeFactory(tok);

        // Then
        tester.assertTrue(node->getTypeId() == t_op_modulus, "Op factory generates modulus node");
}

void given_a_times_token_name_when_it_is_given_to_the_operator_node_factory_then_a_BfTimes_node_is_built(MiTester & tester)
{
        // Given
        TokenName tok = t_op_times;

        // When
        BfNode * node = BfOperatorNodeFactory(tok);

        // Then
        tester.assertTrue(node->getTypeId() == t_op_times, "Op factory generates times node");
}

void given_a_divide_token_name_when_it_is_given_to_the_operator_node_factory_then_a_BfDivide_node_is_built(MiTester & tester)
{
        // Given
        TokenName tok = t_op_divide;

        // When
        BfNode * node = BfOperatorNodeFactory(tok);

        // Then
        tester.assertTrue(node->getTypeId() == t_op_divide, "Op factory generates divide node");
}

void given_power_token_name_when_it_is_given_to_the_operator_node_factory_then_a_BfPower_node_is_built(MiTester & tester)
{
        // Given
        TokenName tok = t_op_pow;

        // When
        BfNode * node = BfOperatorNodeFactory(tok);

        // Then
        tester.assertTrue(node->getTypeId() == t_op_pow, "Op factory generates power node");
}

void given_ellipsis_token_name_when_it_is_given_to_the_operator_node_factory_then_a_BfEllipsis_node_is_built(MiTester & tester)
{
        // Given
        TokenName tok = t_ellipsis;

        // When
        BfNode * node = BfOperatorNodeFactory(tok);

        // Then
        tester.assertTrue(node->getTypeId() == t_ellipsis, "Op factory generates ellipsis node");
}

void given_isnow_token_name_when_it_is_given_to_the_assignment_node_factory_then_a_BfVariableAssignment_node_is_built(MiTester & tester)
{
        // Given
        TokenName tok = t_kwd_isnow;

        // When
        BfNode * node = BfAssignmentNodeFactory(tok);

        // Then
        tester.assertTrue(node->getTypeId() == t_op_assign, "Assign factory generates var assign using isnow node");
}

void given_op_assign_token_name_when_it_is_given_to_the_assignment_node_factory_then_a_BfVariableAssignment_node_is_built(MiTester & tester)
{
        // Given
        TokenName tok = t_op_assign;

        // When
        BfNode * node = BfAssignmentNodeFactory(tok);

        // Then
        tester.assertTrue(node->getTypeId() == t_op_assign, "Assign factory generates var assign using op-assign node");
}

void given_is_token_name_when_it_is_given_to_the_assignment_node_factory_then_a_BfConstantAssignment_node_is_built(MiTester & tester)
{
        // Given
        TokenName tok = t_kwd_is;
        
        // When
        BfNode * node = BfAssignmentNodeFactory(tok);
        
        // Then
        tester.assertTrue(node->getTypeId() == t_kwd_is, "Assign factory generates const assign using is node");
} 

int main()
{
	MiTester tester = MiTester();

	given_a_plus_token_name_when_it_is_given_to_the_operator_node_factory_then_a_BfPlus_node_is_built(tester);
	given_a_minus_token_name_when_it_is_given_to_the_operator_node_factory_then_a_BfMinus_node_is_built(tester);
	given_an_or_token_name_when_it_is_given_to_the_operator_node_factory_then_a_BfOr_node_is_built(tester);
	given_an_and_token_name_when_it_is_given_to_the_operator_node_factory_then_a_BfAnd_node_is_built(tester);
	given_a_greater_than_token_name_when_it_is_given_to_the_operator_node_factory_then_a_BfGreaterThan_node_is_built(tester);
	given_a_less_than_token_name_when_it_is_given_to_the_operator_node_factory_then_a_BfLessThan_node_is_built(tester);
	given_a_greater_than_or_equal_token_name_when_it_is_given_to_the_operator_node_factory_then_a_BfGreaterThanOrEqual_node_is_built(tester);
	given_a_less_than_or_equal_token_name_when_it_is_given_to_the_operator_node_factory_then_a_BfLessThanOrEqual_node_is_built(tester);
	given_an_equal_token_name_when_it_is_given_to_the_operator_node_factory_then_a_BfEqual_node_is_built(tester);
	given_a_not_equal_token_name_when_it_is_given_to_the_operator_node_factory_then_a_BfNotEqual_node_is_built(tester);
	given_a_concat_token_name_when_it_is_given_to_the_operator_node_factory_then_a_BfConcat_node_is_built(tester);
	given_a_modulus_token_name_when_it_is_given_to_the_operator_node_factory_then_a_BfModulus_node_is_built(tester);
	given_a_times_token_name_when_it_is_given_to_the_operator_node_factory_then_a_BfTimes_node_is_built(tester);
	given_a_divide_token_name_when_it_is_given_to_the_operator_node_factory_then_a_BfDivide_node_is_built(tester);
	given_power_token_name_when_it_is_given_to_the_operator_node_factory_then_a_BfPower_node_is_built(tester);
	given_ellipsis_token_name_when_it_is_given_to_the_operator_node_factory_then_a_BfEllipsis_node_is_built(tester);
	given_isnow_token_name_when_it_is_given_to_the_assignment_node_factory_then_a_BfVariableAssignment_node_is_built(tester);
	given_op_assign_token_name_when_it_is_given_to_the_assignment_node_factory_then_a_BfVariableAssignment_node_is_built(tester);

	tester.printResults();
	return 0;
}
