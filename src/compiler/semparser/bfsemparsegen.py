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

def str_to_camel(string):
    return "".join(i[0].upper() + i[1:] for i in string.split(' '))

class SyntaxNodeGenerator(object):
    def __init__(self, key_name, defs):
        self.key_name = key_name
        self.defs = defs

    def print_me(self):
        print self.get_key_name_class_def(), self.defs

def parse_semantics_file(file_name):
    generators = []

    keys = get_keys(file_name)
    tokens = get_tokens(file_name)
    definition_part = [[j.strip() for j in i[1].split('|')] for i in get_key_and_definition_pairs(file_name)]

    if len(keys) != len(definition_part):
        print "Something strange is amuck"
        exit()

    for i in xrange(len(keys)):
        generators.append(SyntaxNodeGenerator(keys[i], definition_part[i]))
        generators[-1].print_me()


def get_tokens(file_name):
    with open(file_name, 'r') as file_stream:
        text = file_stream.read()

    return [i for i in  text.split() if i.startswith("t_")]

def get_keys(file_name):
    key_parts = get_key_and_definition_pairs(file_name)
    ensure_keys_are_valid(i[0] for i in key_parts)

    return [i[0][1:-1] for i in key_parts]


def ensure_keys_are_valid(keys):
    key_names = set()
    for key in keys:
        if key == "":
            print "Cannot use a blank key"
            exit()
        if not key[0] == '<':
            print "Key:", key, "must begin with '<'"
            exit()
        if not key[-1] == '>':
            print "Key:", key, "must end with '>'"
            exit()

        if key in key_names:
            print "Key:", key, "has been defined twice"
            exit()

        key_names.add(key)

def get_key_and_definition_pairs(file_name):
    lines = get_only_valuable_lines(file_name)
    mini = unlines_and_minify(lines)
    stmnts = mini.split(';')
    return [[j.strip() for j in i.split('::=')] for i in stmnts][:-1]

def unlines_and_minify(lines):
    result = "".join(lines)

    while "\t" in result:
        result = result.replace("\t", ' ')

    while '  ' in result:
        result = result.replace('  ', ' ')

    return result

def get_only_valuable_lines(file_name):
    result = []
    with open(file_name, 'r') as file_stream:
        text = file_stream.read()

    for line in text.split('\n'):
        clean_line = line.strip()

        if clean_line == "":             # Blank line
            continue
        if clean_line[0] == "#":         # Comment
            continue

        result.append(line)
    return result

    

if __name__ == '__main__':
    parse_semantics_file("semantics.bfs")
