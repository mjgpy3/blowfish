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
	t_kwd_is = 6,
	t_kwd_isnow = 7,
	t_kwd_not = 8,
	t_kwd_forms = 9,
	t_kwd_are = 10,
	t_kwd_or = 11,
	t_kwd_and = 12,
	t_kwd_for = 13,
	t_kwd_in = 14,
	t_kwd_enum = 15,
	t_kwd_require = 16,
	t_kwd_import = 17,
	t_kwd_until = 18,
	t_kwd_unless = 19,
	t_ellipsis = 20,
	t_param_ident = 21,
	t_integer = 22,
	t_neg_integer = 23,
	t_neg_float = 24,
	t_float = 25,
	t_char = 26,
	t_string = 27,
	t_white_space = 28,
	t_op_plus = 29,
	t_op_minus = 30,
	t_op_times = 31,
	t_op_divide = 32,
	t_op_modulus = 33,
	t_op_assign = 34,
	t_op_pow = 35,
	t_op_concat = 36,
	t_op_dot = 37,
	t_identifier = 38,
	t_neg_ident = 39,
	t_line_ending = 40,
	t_op_eq = 41,
	t_op_lt = 42,
	t_op_leq = 43,
	t_op_gt = 44,
	t_op_geq = 45,
	t_op_noteq = 46,
	t_pipe = 47,
	t_holder_begin = 48,
	t_holder_end = 49,
	t_block_begin = 50,
	t_block_end = 51,
	t_paren_begin = 52,
	t_paren_end = 53
};

#endif

