#!/bin/bash

find .. -name "*.$1" | xargs grep $2 
