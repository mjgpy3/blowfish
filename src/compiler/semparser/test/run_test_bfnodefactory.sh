#!/bin/bash

g++ test_bfnodefactory.cpp ../../../mitest/mitest.cpp ../bfnodefactory.cpp ../bfnodes.cpp ../../scope/bfscopenode.cpp -I .. -I ../../../mitest -I ../../lexer -I ../../scope

./a.out
rm a.out
