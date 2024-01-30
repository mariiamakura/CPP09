#!/bin/bash

echo "test on empry arg"
./RPN ""
echo "----------------------"

echo "test on spaces arg"
./RPN "          "
echo "----------------------"

echo "test on spaces  and numbers arg"
./RPN "    8 9 * 2 /      "
echo "----------------------"

echo "pdf test"
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
echo "----------------------"

echo "pdf test"
./RPN "7 7 * 7 -"
echo "----------------------"

echo "pdf test"
./RPN "1 2 * 2 / 2 * 2 4 - +"
echo "----------------------"

echo "pdf test"
 ./RPN "(1 + 1)"
echo "----------------------"


