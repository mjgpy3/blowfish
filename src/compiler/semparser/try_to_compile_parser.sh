#!/bin/bash

g++ *.cpp ../lexer/foundtoken.cpp ../lexer/bflexer.cpp ../../migrep/migrep.cpp -I ../lexer -I ../../migrep || exit
./a.out

#rm a.out
