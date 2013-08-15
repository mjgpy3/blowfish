#!/usr/bin/env python

from os import popen

if __name__ == '__main__':
    files = [ i for i in popen("find .. -name 'run*'").read().split("\n") if not i in ['', "../tools/run_all_tests.py"] ]
    files += [ i for i in popen("find .. -name 'test*py'").read().split("\n") if not i in ['', "../tools/run_all_tests.py"] ]

    total_tests = 0

    for a_file in files:
        print a_file + ":"
        path = "/".join(a_file.split('/')[:-1])
	file_name = a_file.split('/')[-1]
        a = popen("cd " + path + "; ./" + file_name).read()
        lines = a.split('\n')
        if "Tests run:" in a:
            total_tests += int(lines[1].replace("Tests run:", "")[1:])
        print a

    print "MiTest tests:", total_tests
