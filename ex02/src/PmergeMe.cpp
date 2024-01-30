#include "../include/PmergeMe.hpp"

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe &src) {
    *this = src;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &src) {
    if (this != &src)
        *this = src;
    return *this;
}

void printList(std::list<int> &finList) {
    for (std::list<int>::iterator it = finList.begin(); it != finList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
}

PmergeMe::~PmergeMe() {}

static std::vector<int> mergeVecs(std::vector<int> &left, std::vector<int> &right) {
    std::vector<int> res;

    //merge till one of them not empty
    while (!left.empty() && !right.empty()) {
        if (left.front() <= right.front()) {
            res.push_back(left.front());
            left.erase(left.begin());
        } else {
            res.push_back(right.front());
            right.erase(right.begin());
        }
    }

    while (!left.empty()) {
        res.push_back(left.front());
        left.erase(left.begin());
    }
    while (!right.empty()) {
        res.push_back(right.front());
        right.erase(right.begin());
    }
    return res;
}

static std::vector<int> mergeInsertVec(std::vector<int> &storage) {
    if (storage.size() <= 1)
        return storage;

    //devide numbers into 2 parts
    int middle = storage.size() / 2;
    std::vector<int> left(storage.begin(), storage.begin() + middle);
    std::vector<int> right(storage.begin() + middle, storage.end());

    //recursively sort them
    left = mergeInsertVec(left);
    right = mergeInsertVec(right);

    return mergeVecs(left, right);
}

double PmergeMe::sortVec(int ac, char **av) {
    std::vector<int> storage;

    for (int i = 1; i < ac; i++) {
        storage.push_back(atoi(av[i]));
    }

    std::clock_t startTime = std::clock();
    storage = mergeInsertVec(storage);

    double finTime = static_cast<double>(std::clock() - startTime) / static_cast<double>(CLOCKS_PER_SEC);
    std::cout << "After <sortVec>: ";
    printVec(storage);

    return finTime;
}

static std::list<int> mergeLists(std::list<int> &left, std::list<int> &right) {
    std::list<int> res;

    while (!left.empty() && !right.empty()) {
        if (left.front() <= right.front()) {
            res.push_back(left.front());
            left.erase(left.begin());
        } else {
            res.push_back(right.front());
            right.erase(right.begin());
        }
    }
    while (!left.empty()) {
        res.push_back(left.front());
        left.erase(left.begin());
    }
    while (!right.empty()) {
        res.push_back(right.front());
        right.erase(right.begin());
    }
    return res;
}

static std::list<int> mergeInsertList(std::list<int> &storage) {
    if (storage.size() <= 1)
        return storage;

    //divide list into 2 parts
    int middle = storage.size() / 2;

    std::list<int> left;
    std::list<int> right;

    for (int i = 0; i < middle; i++) {
        left.push_back(storage.front());
        //remove first element
        storage.pop_front();
    }
    right = storage;

    //recursion to sort
    left = mergeInsertList(left);
    right = mergeInsertList(right);

    return mergeLists(left, right);
}

double PmergeMe::sortList(int ac, char **av) {
    std::list<int> storage;

    for (int i = 1; i < ac; i++) {
        storage.push_back(atoi(av[i]));
    }

    std::clock_t startTime = std::clock();

    storage = mergeInsertList(storage);

    double finTime = static_cast<double>(std::clock() - startTime) / static_cast<double>(CLOCKS_PER_SEC);
    std::cout << "After <sortList>: ";
    printList(storage);

    return finTime;

}