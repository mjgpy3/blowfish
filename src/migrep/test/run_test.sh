#!/bin/bash

c++ -I ../ -I ../../mitest/ test_migrep.cpp ../migrep.cpp ../../mitest/mitest.cpp

./a.out

rm ./a.out
