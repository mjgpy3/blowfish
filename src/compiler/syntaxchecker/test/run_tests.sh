#!/bin/bash


for test_file in $(ls *test_*.cpp)
do

    g++ $test_file ../bfnodechecker.cpp ../../semparser/bfnodes.cpp ../../../mitest/mitest.cpp -I ../../lexer -I ../../semparser -I ../  -I ../../../mitest
    ./a.out
    rm a.out

done
