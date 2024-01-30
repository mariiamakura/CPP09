#include "include/PmergeMe.hpp"

void printVec(std::vector<int> &finVec) {
    for (std::vector<int>::iterator it = finVec.begin(); it != finVec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
}

int argCheck(int ac, char **av) {
    try {
        std::vector<int> temp;
        for (int i = 1; i < ac; i++) {
            if (std::string(av[i]).find_first_not_of("0123456789 ") != std::string::npos)
                throw std::invalid_argument("Invalid element");

            char *endptr;
            long longValue = strtol(av[i], &endptr, 10);

            // Check if strtol encountered an error or if the value exceeds INT_MAX or INT_MIN
            if (*endptr != '\0' || longValue > INT_MAX || longValue < INT_MIN)
                throw std::out_of_range("Value exceeds representable range of int");
            temp.push_back((atoi(av[i])));
        }
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int main(int ac, char **av) {
    if (ac < 2) {
        std::cout << "Wrong number of arguments" << std::endl;
        return EXIT_FAILURE;
    }
    if (argCheck(ac, av) == EXIT_FAILURE)
        return EXIT_FAILURE;

    std::cout << "Before: ";
    for (int i = 1; i < ac; i++) {
        std::cout << av[i] << " ";
    }
    std::cout << "\n";

    PmergeMe pmergeMe;
    double timeVec = pmergeMe.sortVec(ac, av);
    double timeList = pmergeMe.sortList(ac, av);

    std::cout << "\n";

    std::cout << "vecList time: " << std::fixed << std::setprecision(6) << timeVec << " seconds" << std::endl;
    std::cout << "sortList time: " << std::fixed << std::setprecision(6) << timeList << " seconds" << std::endl;
}


// for invalid arg ./PmergeMe 345 754 3457 3472 578 345f345