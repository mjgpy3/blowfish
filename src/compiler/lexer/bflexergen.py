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
    "ignore",
    "keyword"
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

            elif current_mode == PARSE_MODES["section_helpers:"]:
                if self.is_definition_line(trim_line):
                    name, regex = self.get_definition_parts(trim_line)

                    self.helpers[name] = regex
        
            elif current_mode == PARSE_MODES["section_tokens:"]:
                if self.is_definition_line(trim_line):
                    name, match = self.get_definition_parts(trim_line)
                    match = self.replace_any_helpers(match)
                    match = self.remove_single_quotes(match)
                    match = match.replace('"', '\\"')

                    self.tokens.append(Token(name, match))

                elif self.is_options_line(trim_line):
                    options = self.get_options(trim_line)

                    self.tokens[-1].options = options

    def remove_single_quotes(self, value):
        parts = [part.replace("'", "") for part in value.split("\\'")]
        return "\\'".join(parts)

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

class TokensToCPlusPlus(object):
    def __init__(self):
        self.struct_name = "Tokens"
        self.array_name = "AllTokens"
        self.array_size_name = "NUM_TOKENS"

    def write_tokens_to_file(self, tokens, definition_name, file_name):
        with open(file_name, 'r') as file_reader:
            text = file_reader.read()

        resultant_lines = []
        in_section = False

        for line in text.split('\n'):
            if not in_section:
                resultant_lines.append(line)

            if "#ifndef " + definition_name in line:
                resultant_lines += self.get_token_structure_code(definition_name, tokens)
                in_section = True

            if "#endif" in line:
                in_section = False
                resultant_lines.append(line)

        with open(file_name, 'w') as file_stream:
            file_stream.write("\n".join(resultant_lines))

    def get_token_structure_code(self, definition_name, tokens):
        return [ self.get_token_section_definition(definition_name) + '\n',
                 self.get_token_struct() + '\n',
                 self.get_number_of_tokens_constant(tokens) + '\n',
                 self.get_token_array_declaration(tokens) + '\n',
                 self.get_token_array_filling_statements(tokens) + '\n']

    def get_token_array_filling_statements(self, tokens):
        result = ""

        for i, token in enumerate(tokens):
            result += self.assign_value_to_array_attribute(token.name, 

        return result

    def assign_value_to_array_attribute(value, attr, index):
        return (self.array_name + "[" + str(index) + "]." +
                attr + " = " + value + ";");

    def get_token_array_declaration(self, tokens):
        return (self.struct_name + " " + 
                self.array_name +"[" + str(len(tokens)) + "];")

    def get_token_section_definition(self, definition_name):
        return '#define ' + definition_name

    def get_number_of_tokens_constant(self, tokens):
        return ('const int ' + self.array_size_name +
                ' = ' + str(len(tokens)) + ';')

    def get_token_struct(self):
        return """typedef struct
{
\tchar* name;
\tchar* match;
\tbool isKeyword;
\tbool savesText;
\tbool isIgnored;
} Token;"""

if __name__ == '__main__':
    validate_args()
    print "Input:", argv[1], "\nOutput:", argv[2]

    parser = TokenFileParser()
    parser.parse(argv[1])

    writer = TokensToCPlusPlus()

    writer.write_tokens_to_file(parser.tokens, "BLOWFISH_TOKENS", argv[2])
