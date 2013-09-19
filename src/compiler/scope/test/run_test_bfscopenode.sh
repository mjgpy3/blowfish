#!/bin/bash

c++ test_bfscopenode.cpp ../bfscopenode.cpp ../../../mitest/mitest.cpp ../../literals/bfnumber.cpp ../../semparser/bfnodes.cpp -I .. -I ../../../mitest -I ../../semparser -I ../../lexer -I ../../literals

./a.out
rm a.out
