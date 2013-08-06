#!/bin/bash

c++ test_bfscopenode.cpp ../bfscopenode.cpp ../../../mitest/mitest.cpp -I .. -I ../../../mitest 

./a.out
rm a.out
