#!/bin/bash

g++ test_bfexecutor.cpp ../../classes/bfclass.cpp ../../classes/bfobject.cpp ../../classes/instancebuilder.cpp ../../classes/bfprimclasses.cpp ../../methods/bfparams.cpp ../../methods/bfmeth.cpp ../../literals/bfnumber.cpp ../../syntaxchecker/bfnodechecker.cpp ../bfexecutor.cpp ../../semparser/bfnodes.cpp ../../../mitest/mitest.cpp ../../scope/bfscopenode.cpp -I .. -I ../../../mitest -I ../../semparser -I ../../lexer -I ../../scope -I ../../syntaxchecker -I ../../literals -I ../../classes -I ../../methods

./a.out
rm a.out
