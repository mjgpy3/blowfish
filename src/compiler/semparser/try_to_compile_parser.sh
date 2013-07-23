#!/bin/bash

c++ *.cpp ../lexer/foundtoken.cpp -I ../lexer
./a.out

rm a.out
