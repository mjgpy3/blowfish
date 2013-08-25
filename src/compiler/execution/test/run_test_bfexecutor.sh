#!/bin/bash

g++ test_bfexecutor.cpp ../../literals/bfnumber.cpp ../../syntaxchecker/bfnodechecker.cpp ../bfexecutor.cpp ../../semparser/bfnodes.cpp ../../../mitest/mitest.cpp ../../scope/bfscopenode.cpp -I .. -I ../../../mitest -I ../../semparser -I ../../lexer -I ../../scope -I ../../syntaxchecker -I ../../literals

./a.out
rm a.out
