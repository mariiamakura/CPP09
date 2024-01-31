#!/bin/bash

 ./PmergeMe
 ./PmergeMe 3 5 9a 7 4 #parse error
 ./PmergeMe 3 5 90000000000000 7 4 #parse error
 ./PmergeMe 3 5 9 -7 4 #parse error
 ./PmergeMe 3 5 9 7 4 45 9 23 456 2 5
 #./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`