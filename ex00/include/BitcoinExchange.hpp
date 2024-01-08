#pragma once

#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdlib>

#define OPEN_FILE_ERR "Error: could not open file."
#define BAD_INPUT "Error: bad input => "


class BitcoinExchange {
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &src);
        BitcoinExchange &operator=(const BitcoinExchange &src);
        ~BitcoinExchange();

        void readData(std::ifstream &bitcoinData);

        static bool isDateFormat(const std::string &str);
        static bool isDateValid(const std::string &src);
        static bool isRateValid(const std::string &rate);

        float getRateFromDataBase(const std::string &date);
    private:
        std::map<std::string, float> dataBase;
};