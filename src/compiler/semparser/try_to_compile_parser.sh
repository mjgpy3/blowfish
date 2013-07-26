#!/bin/bash

g++ *.cpp ../lexer/foundtoken.cpp ../lexer/bflexer.cpp ../../migrep/migrep.cpp -I ../lexer -I ../../migrep
./a.out

#rm a.out
