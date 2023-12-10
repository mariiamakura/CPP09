#include "../include/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src) {
    *this = src;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &src) {
    if (this != &src)
        this->dataBase = src.dataBase;
    return (*this);
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::readData(std::ifstream &bitcoinData) {
    std::string line;
    size_t coma;

    //skip the first line
    std::getline(bitcoinData, line);
    while (std::getline(bitcoinData, line)) {
        coma = line.find(',');
        std::string bitcoinRate = line.substr(coma + 1);
        const char *rate = strcpy(new char[bitcoinRate.length() + 1], bitcoinRate.c_str());
        this->dataBase[line.substr(0, coma)] = std::atof(rate);
        delete (rate);
    }
    bitcoinData.close();
}

bool BitcoinExchange::isDateFormat(const std::string &str) {
    if (str.empty()) {
        std::cerr << "Empty" << std::endl;
        return (false);
    }
    size_t firstD = str.find('-');
    size_t secondD = str.find('-', firstD + 1);

    if (firstD == std::string::npos || secondD == std::string::npos ||
    str.find_first_not_of("0123456789-.") != std::string::npos) {
        std::cerr << BAD_INPUT << str << std::endl;
        return (false);
    }
    return (true);
}

static unsigned int myAtoi(const std::string &src) {
    unsigned int n;
    std::stringstream ss(src);

    ss >> n;
    return n;

}

bool BitcoinExchange::isDateValid(const std::string &src) {
    std::string str;
    int year, month, day;
    std::istringstream ss(src);

    int i = 0;
    while (std::getline(ss, str, '-')) {
        if (i == 0) {
            year = myAtoi(str);
            if (year < 2009 || year > 2022) {
                std::cerr << "YEAR NOT IN DATABASE " << src << std::endl;
                return false;
            }
        }
        else if (i == 1) {
            month = myAtoi(str);
            if (month < 1 || month > 12) {
                std::cerr << "INCORRECT MONTH " << src << std::endl;
                return false;
            }
        }
        else if (i == 2) {
            day = myAtoi(str);
            if (day < 1 || day > 31) {
                std::cerr << "INCORRECT DAY " << src << std::endl;
                return false;
            }
        }
        i++;
    }
    if (i != 3) {
        std::cerr << "INCORRECT DATE " << str << std::endl;
        return false;
    }
    return true;
}

bool BitcoinExchange::isRateValid(const std::string &rate) {
    if (rate.empty() || rate.find_first_not_of("0123456789.-") != std::string::npos ||
        rate.at(0) == '.' || rate.find('.', rate.length() - 1) != std::string::npos)
        std::cerr << "Error: not valid amount of bitcoins " << rate << std::endl;
    else if (rate.at(0) == '-')
        std::cerr << "Error: not a positive number " << rate << std::endl;
    else if (rate.length() > 10 || (rate.length() == 10 && rate > "2147483647"))
        std::cerr << "Error: too large a number " << rate << std::endl;
    else
        return true;
    return false;
}

float BitcoinExchange::getRateFromDataBase(const std::string &date) {
    if (this->dataBase.count(date) > 0) {
        return (this->dataBase.at(date));
    }
    return (--this->dataBase.lower_bound(date))->second;
}
