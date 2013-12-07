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

#ifndef BLOWFISH_TOKEN_NAMES
#define BLOWFISH_TOKEN_NAMES

enum TokenName 
{
	t_kwd_class = 0,
	t_kwd_module = 1,
	t_kwd_meth = 2,
	t_kwd_if = 3,
	t_kwd_elseif = 4,
	t_kwd_else = 5,
	t_kwd_self = 6,
	t_kwd_super = 7,
	t_kwd_is = 8,
	t_kwd_isnow = 9,
	t_kwd_not = 10,
	t_kwd_forms = 11,
	t_kwd_or = 12,
	t_kwd_lambda = 13,
	t_kwd_and = 14,
	t_kwd_for = 15,
	t_kwd_in = 16,
	t_kwd_enum = 17,
	t_kwd_require = 18,
	t_kwd_import = 19,
	t_kwd_until = 20,
	t_kwd_unless = 21,
	t_kwd_return = 22,
	t_ellipsis = 23,
	t_param_ident = 24,
	t_neg_float = 25,
	t_float = 26,
	t_integer = 27,
	t_neg_integer = 28,
	t_string = 29,
	t_white_space = 30,
	t_op_plus = 31,
	t_op_minus = 32,
	t_op_times = 33,
	t_op_divide = 34,
	t_op_modulus = 35,
	t_op_assign = 36,
	t_op_pow = 37,
	t_op_concat = 38,
	t_op_dot = 39,
	t_identifier = 40,
	t_neg_ident = 41,
	t_line_ending = 42,
	t_op_eq = 43,
	t_op_lt = 44,
	t_op_leq = 45,
	t_op_gt = 46,
	t_op_geq = 47,
	t_op_noteq = 48,
	t_pipe = 49,
	t_holder_begin = 50,
	t_holder_end = 51,
	t_block_begin = 52,
	t_block_end = 53,
	t_paran_begin = 54,
	t_neg_paran = 55,
	t_paran_end = 56,
	t_root,
	t_neg,
	t_list,
	t_dict,
	t_set,
	t_empty,
	end_tokens
};

#endif

