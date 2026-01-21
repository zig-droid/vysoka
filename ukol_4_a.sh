#!/bin/bash

for i in $(seq -w 0001 1000)  #(seq -w 0001 1000) mohu nahradit (0001..1000)
do
    day=$((RANDOM % 31 + 1))
    month=$((RANDOM % 12 + 1))
    year=$((RANDOM % 201 + 1825))
    echo $day/$month/$year > foo$i.txt
done
