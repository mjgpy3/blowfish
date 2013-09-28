#!/bin/bash

g++ test_bfclass.cpp ../../literals/bfnumber.cpp ../../methods/bfmeth.cpp ../bfclass.cpp ../bfobject.cpp ../../scope/bfscopenode.cpp ../../../mitest/mitest.cpp ../../semparser/bfnodes.cpp -I ../../../mitest -I .. -I ../../semparser -I ../../lexer -I ../../literals -I ../../scope -I ../../methods || exit

./a.out
rm a.out
