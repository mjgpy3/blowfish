#!/usr/bin/env python
# Author: Michael Gilliland

"""
    A lexer for generating token connections in blowfish
"""

from sys import argv

PARSE_MODES = {
    "none": 0,
    "section_helpers:": 1,
    "section_tokens:": 2
}

OPTIONS = [
    "save_text",
    "ignore"
]

class Token(object):
    """
        Token entities, as parsed from a token file
    """
    def __init__(self, name="", match="", options=[]):
        self.name = name
        self.match = match
        self.options = options

    def __repr__(self):
        return '"' + self.name + ": " +\
               self.match + " (" + ", ".join(self.options) + ")" + '"'

def validate_args():
    if len(argv) < 3:
        usage()
        exit()
    try:
        f = open(argv[1])
        f.close()
    except IOError:
        usage()
        exit()

    if not argv[2].endswith(".cpp"):
        argv[2] += ".cpp"

def usage():
    print "bflexer.py <token_file> <output_name>.cpp"

class TokenFileParser(object):
    def __init__(self):
        self.tokens = []
        self.helpers = {}

    def parse(self, file_name):
        current_mode = PARSE_MODES["none"]

        with open(file_name) as file_stream:
            file_text = file_stream.read()

        for line in file_text.split('\n'):
            trim_line = line.strip()

            if trim_line == '':
                continue
    
            elif trim_line in PARSE_MODES:
                current_mode = PARSE_MODES[trim_line]
                print "In mode", trim_line

            elif current_mode == PARSE_MODES["section_helpers:"]:
                if self.is_definition_line(trim_line):
                    name, regex = self.get_definition_parts(trim_line)

                    self.helpers[name] = regex
        
            elif current_mode == PARSE_MODES["section_tokens:"]:
                if self.is_definition_line(trim_line):
                    name, match = self.get_definition_parts(trim_line)
                    match = self.replace_any_helpers(match)

                    self.tokens.append(Token(name, match))

                elif self.is_options_line(trim_line):
                    options = self.get_options(trim_line)

                    self.tokens[-1].options = options
        print self.helpers

    def get_options(self, line):
        return_line = line[1:-1]

        return [o.strip() for o in return_line.split(',') if o in OPTIONS]

    def get_definition_parts(self, line):
        parts = line.split("->")
        return (parts[0].strip(), parts[1].strip())

    def is_definition_line(self, line):
        return "->" in line

    def is_options_line(self, line):
        return "[" == line[0] and "]" == line[-1]

    def replace_any_helpers(self, name):
        return_line = name
        for helper in self.helpers:
            if '{'+helper+'}' in return_line:
                return_line = return_line.replace('{'+helper+'}', self.helpers[helper])

        return return_line

if __name__ == '__main__':
    validate_args()
    print "Input:", argv[1], "\nOutput:", argv[2]

    parser = TokenFileParser()
    parser.parse(argv[1])

    for token in parser.tokens:
        print token.name, '->', token.match
