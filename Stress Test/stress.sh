#!/bin/bash

g++ gen.cpp -O2 -o gen
g++ a.cpp -O2 -o sol
g++ check.cpp -O2 -o check

for((i=1;;i++))
do
    echo "Test $i"

    ./gen > input.txt
    ./sol < input.txt > output.txt

    cat input.txt output.txt | ./check > verdict.txt

    if grep -q "OK" verdict.txt
    then
        echo "OK"
    else
        echo "Found failing test!"
        cat input.txt
        cat output.txt
        break
    fi
done