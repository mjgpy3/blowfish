#!/bin/bash

c++ test_bfscopenode.cpp ../../classes/bfobject.cpp ../../../migrep/migrep.cpp ../../literals/bfnumber.cpp ../../classes/bfclass.cpp ../bfscopenode.cpp ../../../mitest/mitest.cpp ../../semparser/bfnodes.cpp -I .. -I ../../../mitest -I ../../semparser -I ../../lexer -I ../../classes -I ../../literals -I ../../methods

./a.out
rm a.out
