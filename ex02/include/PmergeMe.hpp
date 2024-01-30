#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <iomanip>
#include <climits>

class PmergeMe {
    public:
        PmergeMe();
        PmergeMe(const PmergeMe &src);
        PmergeMe &operator=(const PmergeMe &src);
        ~PmergeMe();

        double sortVec(int ac, char **av);
        double sortList(int ac, char **av);
};

void printVec(std::vector<int> &finVec);