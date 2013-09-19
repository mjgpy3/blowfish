#!/bin/bash

c++ ../literals/bfnumber.cpp ../semparser/bfnodefactory.cpp ../scope/bfscopenode.cpp test_integration_lexer_astbuilder.cpp ../syntaxchecker/bfnodechecker.cpp ../../mitest/mitest.cpp ../../migrep/migrep.cpp ../lexer/foundtoken.cpp ../semparser/bfnodes.cpp ../semparser/astbuilder.cpp ../lexer/bflexer.cpp -I ../../mitest -I ../lexer -I ../../migrep -I ../semparser -I ../syntaxchecker -I ../scope -I ../literals || exit

./a.out
rm a.out
rm test_file.bf
