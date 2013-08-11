#!/bin/bash

function remove_by_extension {

for item in $(find .. -name $1)
do
  echo "Deleting: $item"
  rm "$item"
done


}

for ext in "*.swp" "*.pyc" "*.out" "*.gch"
do
  remove_by_extension $ext
done
