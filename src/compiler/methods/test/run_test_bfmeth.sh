#!/bin/bash

g++ test_bfmeth.cpp ../../literals/bfnumber.cpp ../../classes/bfclass.cpp ../../classes/bfobject.cpp ../bfmeth.cpp ../../scope/bfscopenode.cpp ../../../mitest/mitest.cpp ../../semparser/bfnodes.cpp -I ../../../mitest -I .. -I ../../semparser -I ../../lexer -I ../../literals -I ../../scope -I ../../classes || exit

./a.out
rm a.out
