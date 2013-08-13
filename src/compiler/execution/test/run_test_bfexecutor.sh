#!/bin/bash

g++ test_bfexecutor.cpp ../../syntaxchecker/bfnodechecker.cpp ../bfexecutor.cpp ../../semparser/bfnodes.cpp ../../../mitest/mitest.cpp ../../scope/bfscopenode.cpp -I .. -I ../../../mitest -I ../../semparser -I ../../lexer -I ../../scope -I ../../syntaxchecker

./a.out
rm a.out
