#!/bin/bash

for i in "*.py" "*.cpp" "*.h"
do
  find .. -name $i | xargs grep "PCFR"
done
