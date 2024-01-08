#include "include/BitcoinExchange.hpp"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <map>


static int errorMsg(std::string errorM) {
    std::cerr << errorM << std::endl;
    return (EXIT_FAILURE);
}

static void checkInput(std::ifstream &inputData, BitcoinExchange &btc) {
    std::string line;

    std::getline(inputData, line);
    while (std::getline(inputData, line)) {
        size_t d = line.find('|');
        if (d == std::string::npos || line.length() < d + 2) {
            std::cerr << BAD_INPUT << line << std::endl;
            continue;
        }
        std::string date = line.substr(0, d - 1);
        if (!BitcoinExchange::isDateValid(date) || !BitcoinExchange::isDateFormat(date))
            continue;

        std::string rateStr = line.substr(d + 2);

        if (!BitcoinExchange::isRateValid(rateStr))
            continue;

        const char *ratePtr = strcpy(new char[rateStr.length() + 1], rateStr.c_str());
        float rate = std::atof(ratePtr);
        std::cout << date << " => " << rate << " = " << std::setprecision(2) << rate * btc.getRateFromDataBase(date) << std::endl;
        delete ratePtr;
    }
}

int main(int ac, char **av)
{
    if (ac != 2)
        return (errorMsg(OPEN_FILE_ERR));
    //create a stream to read input data
    std::ifstream inputData(av[1], std::ifstream::in);
    if (!inputData.is_open())
        return (errorMsg(OPEN_FILE_ERR));
    //another stream for bitcoin exchange rate
    std::ifstream bitcoinData("data.csv", std::ifstream::in);
    if (!bitcoinData.is_open())
        return (errorMsg(OPEN_FILE_ERR));

    BitcoinExchange btc;
    btc.readData(bitcoinData);

    //check input file
    checkInput(inputData, btc);
    inputData.close();
    bitcoinData.close();
    return EXIT_SUCCESS;

}