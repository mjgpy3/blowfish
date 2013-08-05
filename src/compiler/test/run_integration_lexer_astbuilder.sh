#!/bin/bash

c++ test_integration_lexer_astbuilder.cpp ../syntaxchecker/bfnodechecker.cpp ../../mitest/mitest.cpp ../../migrep/migrep.cpp ../lexer/foundtoken.cpp ../semparser/bfnodes.cpp ../semparser/astbuilder.cpp ../lexer/bflexer.cpp -I ../../mitest -I ../lexer -I ../../migrep -I ../semparser -I ../syntaxchecker

./a.out
rm a.out
rm test_file.bf
