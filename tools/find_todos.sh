#!/bin/bash

for i in "*.py" "*.cpp" "*.h" "*.md"
do
  find .. -name $i | xargs grep "TODO"
done
