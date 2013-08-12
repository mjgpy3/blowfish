#!/bin/bash


for test_file in $(ls *test_*.cpp)
do

    g++ $test_file ../bfnodechecker.cpp ../../semparser/bfnodes.cpp ../../../mitest/mitest.cpp ../../scope/bfscopenode.cpp -I ../../lexer -I ../../semparser -I ../  -I ../../../mitest -I ../../scope
    ./a.out
    rm a.out

done
