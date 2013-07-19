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

def parse_semantics_file(file_name):
    keys = get_keys(file_name)
    tokens = get_tokens(file_name)

    definition_part = [[j.strip() for j in i[1].split('|')] for i in get_key_and_definition_pairs(file_name)]

    print keys

    for i in definition_part:
        print [[k.strip() for k in j.split('->')] for j in i]


    # TODO: Write code to parse file and reduce semantic items to list of only tokens (with gen code)

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
    return [[j.strip() for j in i.split('::=')] for i in stmnts]

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
