#!/bin/bash

g++ test_bfnodefactory.cpp ../../methods/bfmeth.cpp ../../methods/bfparams.cpp ../../classes/bfclass.cpp ../../classes/bfobject.cpp ../../literals/bfnumber.cpp ../../../mitest/mitest.cpp ../bfnodefactory.cpp ../bfnodes.cpp ../../scope/bfscopenode.cpp -I .. -I ../../../mitest -I ../../lexer -I ../../scope -I ../../literals -I ../../classes -I ../../methods

./a.out
rm a.out
