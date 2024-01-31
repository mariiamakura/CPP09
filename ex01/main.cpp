#include "include/RPN.hpp"

int ft_error(const std::string &err) {
    std::cout << err << std::endl;
    return (1);
}

int main(int ac, char **av) {

    RPN test;
    if (ac != 2) {
        return (ft_error("Wrong number of arguments"));
    }
    //check numbers and operators
    //get expretion
    if (!test.checkParam(av[1]))
        return (ft_error("Wrong arguments"));
    size_t res;
    try {
        res = test.calculate(av[1]);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    std::cout << res << std::endl;
}