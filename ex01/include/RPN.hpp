#pragma once

#include <iostream>
#include <stack>
#include <exception>
#include <string>
#include <sstream>
#include <cstdlib>

class RPN {
    private:
        std::stack<int> _num_stack;

    public:
        RPN();
        RPN(const RPN &src);
        RPN &operator=(const RPN &src);
        ~RPN();

        bool checkParam(const std::string &av);
        size_t calculate(const std::string &av);

        class WrongArgument : public std::exception {
        public:
            virtual const char* what() const throw();
        };
};