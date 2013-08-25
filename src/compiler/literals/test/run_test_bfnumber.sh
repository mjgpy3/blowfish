#!/bin/bash

g++ test_bfnumber.cpp ../bfnumber.cpp ../../../mitest/mitest.cpp -I ../../../mitest -I ..

./a.out
rm a.out
