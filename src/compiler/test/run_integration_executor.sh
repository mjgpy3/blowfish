#!/bin/bash

c++ ../classes/bfclass.cpp ../classes/bfobject.cpp ../methods/bfmeth.cpp ../literals/bfnumber.cpp ../execution/bfexecutor.cpp ../semparser/bfnodefactory.cpp ../scope/bfscopenode.cpp test_integration_executor.cpp ../syntaxchecker/bfnodechecker.cpp ../../mitest/mitest.cpp ../../migrep/migrep.cpp ../lexer/foundtoken.cpp ../semparser/bfnodes.cpp ../semparser/astbuilder.cpp ../lexer/bflexer.cpp -I ../../mitest -I ../lexer -I ../../migrep -I ../semparser -I ../syntaxchecker -I ../scope -I ../execution -I ../literals -I ../classes -I ../methods || exit

./a.out
rm a.out
rm test_file.bf
