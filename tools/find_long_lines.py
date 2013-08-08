#!/usr/bin/env python

from os import popen

SRC_FILES = ["*.cpp", "*.py", "*.h", "*.sh"]
IGNORE_IF_CONTAINS = ["//", "tester", "MiTester", "c++", "g++", "Franklin"]

if __name__ == "__main__":
    for file_type in SRC_FILES:
        print "Now looking at:", file_type
        files = [ i for i in popen("find .. -name '%s'" % file_type).read().split('\n')  if i ]

        for a_file in files:
            with open(a_file, 'r') as f:
                line_no = 0
                for line in f.read().split('\n'):
                    line_no += 1
                    if len(line) > 80:
                        report = True
                        for ignore in IGNORE_IF_CONTAINS:
                            if ignore in line:
                                report = False
                                break
                        if report:
                            print a_file + "(" + str(line_no) + "):", line
