#!/bin/bash

g++ test_instancebuilder.cpp ../instancebuilder.cpp ../../literals/bfnumber.cpp ../../methods/bfmeth.cpp ../bfprimclasses.cpp ../bfclass.cpp ../bfobject.cpp ../../scope/bfscopenode.cpp ../../../mitest/mitest.cpp ../../semparser/bfnodes.cpp -I ../../../mitest -I .. -I ../../semparser -I ../../lexer -I ../../literals -I ../../scope -I ../../methods || exit

./a.out
rm a.out
