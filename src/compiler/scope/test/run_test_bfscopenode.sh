#!/bin/bash

c++ test_bfscopenode.cpp ../bfscopenode.cpp ../../../mitest/mitest.cpp ../../semparser/bfnodes.cpp -I .. -I ../../../mitest -I ../../semparser -I ../../lexer

./a.out
rm a.out
