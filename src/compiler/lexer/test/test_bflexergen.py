#!/usr/bin/env python

"""
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
"""

import unittest

import sys
sys.path.append("..")
import bflexergen

class TestBflexergen(unittest.TestCase):
    def setUp(self):
        self.parser = bflexergen.TokenFileParser()

    def test_parser_does_nothing_for_an_empty_section_file(self):
        self.parser.parse('test_files/blank_token_list.bft')

        self.assertEqual([], self.parser.tokens)
        self.assertEqual({}, self.parser.helpers)

    def test_parser_correctly_serializes_a_simple_token_file(self):
        self.parser.parse('test_files/simple_token_file.bft')

        single_token = self.parser.tokens[0]

        self.assertEqual("identifier", single_token.name)
        self.assertEqual("Something", single_token.match)

    def test_parser_strips_single_quotes_unless_they_are_escaped(self):
        self.parser.parse("test_files/escaped_quote.bft")

        single_token = self.parser.tokens[0]

        self.assertEqual("identifier", single_token.name)
        self.assertEqual("Some\\'thing", single_token.match)

    def test_parser_unescaped_double_quotes_come_parsed_as_escaped(self):
        self.parser.parse("test_files/double_quote.bft")

        single_token = self.parser.tokens[0]

        self.assertEqual("identifier", single_token.name)
        self.assertEqual('Some\\"thing', single_token.match)

    def test_get_definition_parts_splits_on_the_arrow_and_other_arrows_are_not_affected(self):
        answer = self.parser.get_definition_parts("something -> dsaf-> + 5 ->7  ")
        expected = ("something", "dsaf-> + 5 ->7")

        self.assertEqual(expected, answer)

    def test_get_definition_parts_works_for_the_odd_case_of_just_an_arrow(self):
        answer = self.parser.get_definition_parts("arrow -> '->'")
        expected = ("arrow", "'->'")

        self.assertEqual(expected, answer)

def main():
    unittest.main()

if __name__ == '__main__':
    main()
