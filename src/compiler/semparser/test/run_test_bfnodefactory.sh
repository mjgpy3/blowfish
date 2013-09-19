#!/bin/bash

g++ test_bfnodefactory.cpp ../../literals/bfnumber.cpp ../../../mitest/mitest.cpp ../bfnodefactory.cpp ../bfnodes.cpp ../../scope/bfscopenode.cpp -I .. -I ../../../mitest -I ../../lexer -I ../../scope -I ../../literals

./a.out
rm a.out
