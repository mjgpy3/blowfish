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
	t_kwd_class = 0,	// C
	t_kwd_module = 1,	// C
	t_kwd_meth = 2,		// C
	t_kwd_if = 3,		// C
	t_kwd_elseif = 4,	// C
	t_kwd_else = 5,		// C
	t_kwd_is = 6,		// C
	t_kwd_isnow = 7,	// C
	t_kwd_not = 8,		// C
	t_kwd_forms = 9,	// C
	t_kwd_are = 10,		// C
	t_kwd_or = 11,		// C
	t_kwd_and = 12,		// C
	t_kwd_for = 13,		// C
	t_kwd_in = 14,		// C
	t_kwd_enum = 15,        // C
	t_kwd_require = 16,	// C
	t_kwd_import = 17,	// C
	t_kwd_until = 18,	
	t_kwd_unless = 19,
	t_ellipsis = 20,	// C
	t_param_ident = 21,	// C
	t_integer = 22,		// C
	t_neg_integer = 23,	// C
	t_neg_float = 24,	// C
	t_float = 25,		// C
	t_char = 26,		// C
	t_string = 27,		// C
	t_white_space = 28,	// C
	t_op_plus = 29,		// C
	t_op_minus = 30,	// C
	t_op_times = 31,	// C
	t_op_divide = 32,	// C
	t_op_modulus = 33,	// C
	t_op_assign = 34,	// C
	t_op_pow = 35,		// C
	t_op_concat = 36,	// C
	t_op_dot = 37,		// C
	t_identifier = 38,	// C
	t_neg_ident = 39,	// C
	t_line_ending = 40,	// C
	t_op_eq = 41,		// C
	t_op_lt = 42,		// ...
	t_op_leq = 43,
	t_op_gt = 44,
	t_op_geq = 45,
	t_op_noteq = 46,
	t_pipe = 47,
	t_holder_begin = 48,
	t_holder_end = 49,
	t_block_begin = 50,
	t_block_end = 51,
	t_paran_begin = 52,
	t_neg_paran = 53,
	t_paran_end = 54	// ... C:w
};

#endif

