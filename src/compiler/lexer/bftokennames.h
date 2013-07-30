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
	t_kwd_or = 10,
	t_kwd_and = 11,
	t_kwd_for = 12,
	t_kwd_in = 13,
	t_kwd_enum = 14,
	t_kwd_require = 15,
	t_kwd_import = 16,
	t_kwd_until = 17,
	t_kwd_unless = 18,
	t_ellipsis = 19,
	t_param_ident = 20,
	t_integer = 21,
	t_neg_integer = 22,
	t_neg_float = 23,
	t_float = 24,
	t_char = 25,
	t_string = 26,
	t_white_space = 27,
	t_op_plus = 28,
	t_op_minus = 29,
	t_op_times = 30,
	t_op_divide = 31,
	t_op_modulus = 32,
	t_op_assign = 33,
	t_op_pow = 34,
	t_op_concat = 35,
	t_op_dot = 36,
	t_identifier = 37,
	t_neg_ident = 38,
	t_line_ending = 39,
	t_op_eq = 40,
	t_op_lt = 41,
	t_op_leq = 42,
	t_op_gt = 43,
	t_op_geq = 44,
	t_op_noteq = 45,
	t_pipe = 46,
	t_holder_begin = 47,
	t_holder_end = 48,
	t_block_begin = 49,
	t_block_end = 50,
	t_paran_begin = 51,
	t_neg_paran = 52,
	t_paran_end = 53
};

#endif

