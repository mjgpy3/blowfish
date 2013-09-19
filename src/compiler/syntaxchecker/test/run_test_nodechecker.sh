#!/bin/bash


for test_file in $(ls *test_*.cpp)
do

    g++ $test_file ../../literals/bfnumber.cpp ../bfnodechecker.cpp ../../semparser/bfnodes.cpp ../../../mitest/mitest.cpp ../../scope/bfscopenode.cpp -I ../../lexer -I ../../semparser -I ../  -I ../../../mitest -I ../../scope -I ../../literals
    ./a.out
    rm a.out

done
