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


"""
    A code generator for blowfish's lexer
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
                    match = match.replace('\.', '\\\\.')

                    self.tokens.append(Token(name, match))

                elif self.is_options_line(trim_line):
                    options = self.get_options(trim_line)

                    self.tokens[-1].options = options

    def is_token_engine_char(self, value):
	return len(value) == 1 and value in "{}[]+*|\\.()"

    def remove_single_quotes(self, value):
	result = ""
        in_quote_mode = False
        ignore_next = False

        for i, c in enumerate(value):
            print "Processing", c
            if ignore_next:
                ignore_next = False
                continue
            if c == "'":
                in_quote_mode = not in_quote_mode
            else:
                if c == '\\' and value[i+1] == "'":
                    result += "'"
                    ignore_next = True

                elif in_quote_mode:
                    if c == '.':
                        result += "\."
                    elif self.is_token_engine_char(c):
                        result += "\\" + "\\" + c[-1]
                    else:
                        result += c
                else:
                    if c == '\\':
                        result += '\\' + c
                    else:
                        result += c

        return result

    def get_options(self, line):
        return_line = line[1:-1]

        return [o.strip() for o in return_line.split(',') if o in OPTIONS]

    def get_definition_parts(self, line):
        parts = line.split("->")
        return (parts[0].strip(), "->".join(parts[1:]).strip())

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
        self.struct_name = "Token"
        self.array_name = "AllTokens"
        self.array_size_name = "NUM_TOKENS"
        self.enum_name = "TokenName"

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

        with open("bftokennames.h", 'r') as f:
            text = f.read()

        results = []
        section = False

        for line in text.split("\n"):
            if line.strip() == "#define BLOWFISH_TOKEN_NAMES":
                section = True
                results.append("#define BLOWFISH_TOKEN_NAMES")
                results.append('\n'+self.get_token_enum(tokens)+'\n')

            if line.strip() == "#endif":
                section = False

            if not section:
                results.append(line)
            else:
                pass

        with open("bftokennames.h", 'w') as f:
            f.write("\n".join(results))

    def get_token_structure_code(self, definition_name, tokens):
        return [ self.get_comment("bflexergen.py") + '\n',
                 self.get_token_section_definition(definition_name) + '\n',
                 self.get_number_of_tokens_constant(tokens) + '\n',
                 self.options_to_cpp_arrays(tokens) + '\n',
                 self.match_to_cpp_array(tokens) + '\n']

    def options_to_cpp_arrays(self, tokens):
        array_dict = {}

        for option in OPTIONS:
            array_dict[option] = []

        for token in tokens:
            for option in OPTIONS:
                array_dict[option].append(int(option in token.options))

        result = []

        for option in array_dict:
            result.append("int " + self.underscores_to_camel(option) + "[] = " +
                          "{" + ", ".join(str(i) for i in array_dict[option]) + "};")

        return "\n".join(result)

    def get_init_token_function(self):
        return """void init_token(int index)
{
\t""" + self.array_name +  """[index].type = (""" + self.enum_name +  """)index;
\t""" + self.array_name + """[index].match = Matches[index];
\t""" + self.array_name + """[index].savesText = SaveText[index];
\t""" + self.array_name + """[index].isIgnored = Ignore[index];
}
"""

    def match_to_cpp_array(self, tokens):
        return "string Matches[] = {" + ", ".join('"'+i.match+'"' for i in tokens) + "};"

    def underscores_to_camel(self, thing):
        return "".join(i[0].upper() + i[1:] for i in thing.split("_"))

    def get_comment(self, generator_name):
        return "// Code in this section generated by " + generator_name

    def get_token_array_filling_statements(self, tokens):
        result = """void setup_tokens()
{
\tfor (int i = 0; i < %s; i += 1)
\t{
\t\tinit_token(i);
\t}
}
""" % self.array_size_name
        return result

    def cpp_contains(self, thing, items):
        if thing in items:
            return "true"
        return "false"

    def assign_value_to_array_attribute(self, value, attr, index):
        return (self.first_part_of_assign(attr, index) + value + ";\n")

    def first_part_of_assign(self, attr, index):
        return (self.array_name + "[" + str(index) + "]." +
                attr + " = ")

    def get_token_enum(self, tokens):
        return "enum " + self.enum_name + " \n{\n\t" + ", ".join("t_" + i.name for i in tokens) + "\n};"

    def get_token_array_declaration(self, tokens):
        return (self.struct_name + " * " + self.array_name + " = new " + 
               self.struct_name + "[" + self.array_size_name + "];")

    def get_token_section_definition(self, definition_name):
        return '#define ' + definition_name

    def get_number_of_tokens_constant(self, tokens):
        return ('const int ' + self.array_size_name +
                ' = ' + str(len(tokens)) + ';')

    def get_token_struct(self):
        return "struct " + self.struct_name + """ 
{
\t%s type;
\tstring match;
\tbool savesText;
\tbool isIgnored;
}; """ % self.enum_name

if __name__ == '__main__':
    validate_args()
    print "Input:", argv[1], "\nOutput:", argv[2]

    parser = TokenFileParser()
    parser.parse(argv[1])

    writer = TokensToCPlusPlus()

    writer.write_tokens_to_file(parser.tokens, "BLOWFISH_TOKENS", argv[2])
