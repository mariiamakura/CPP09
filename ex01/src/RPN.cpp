#include "../include/RPN.hpp"

RPN::RPN() {};

RPN::RPN(const RPN &src) {
        *this = src;
}

RPN &RPN::operator=(const RPN &src) {
    if (this != &src)
        *this = src;
    return (*this);
}

RPN::~RPN() {};

const char *RPN::WrongArgument::what() const throw() {
    return "RPN : wrong argument";
}

bool RPN::checkParam(const std::string &av) {

    if (av.empty() || av.find_first_not_of(" ") == std::string::npos)
        return false;
    if (av.find_first_not_of("0123456789+-/* ") != std::string::npos)
        return false;
    std::stringstream anStream(av);
    std::string num;

    while (anStream >> num)
    {
        //std::cout << "lenght: " << num.length() << std::endl;
        if (num.length() > 1 || ((num != "*" || num != "/" || num != "+" || num != "-") &&
                atoi(num.c_str()) > 10)) {
            return false;
        }
    }
    return true;
}

size_t RPN::calculate(const std::string &av) {
    std::stringstream anStream(av);
    std::string num;
    int left;
    int right;
    size_t result;

    while (anStream >> num) {
        if (num == "*" || num == "/" || num == "+" || num == "-") {
            if (this->_num_stack.size() < 2)
                throw WrongArgument();
            right = this->_num_stack.top();
            this->_num_stack.pop();
            left = this->_num_stack.top();
            this->_num_stack.pop();
            switch (num.at(0)) {
                case '+': {
                    result = left + right;
                    break;
                }
                case '-': {
                    result = left - right;
                    break;
                }
                case '/': {
                    if (right == 0)
                        throw WrongArgument();
                    result = left / right;
                    break;
                }
                case '*': {
                    result = left * right;
                    break;
                }
            }
            this->_num_stack.push(result);
        } else {
            this->_num_stack.push(atoi(num.c_str()));
        }
    }
    return this->_num_stack.top();
}