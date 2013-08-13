#!/bin/bash

g++ test_bfexecutor.cpp ../bfexecutor.cpp ../../../mitest/mitest.cpp -I .. -I ../../../mitest

./a.out
rm a.out
