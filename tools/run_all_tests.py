#!/usr/bin/env python

from os import popen

if __name__ == '__main__':
    files = [ i for i in popen("find .. -name 'run*'").read().split("\n") if not i in ['', "../tools/run_all_tests.py"] ]

    for a_file in files:
        print a_file + ":"
        path = "/".join(a_file.split('/')[:-1])
	file_name = a_file.split('/')[-1]
        a = popen("cd " + path + "; ./" + file_name).read()
        print a
