#!/usr/bin/env python

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

    def test_parser_doesnt_need_double_quotes_to_be_escaped(self):
        self.parser.parse("test_files/double_quote.bft")

        single_token = self.parser.tokens[0]

        self.assertEqual("identifier", single_token.name)
        self.assertEqual('Some"thing', single_token.match)

def main():
    unittest.main()

if __name__ == '__main__':
    main()
