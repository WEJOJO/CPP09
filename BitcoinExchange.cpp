#include <iomanip>
#include <iostream>

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {
    std::cout << std::setw(15) << "[BitcoinExchange] "
              << "create!!" << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &ref) {
    *this = ref;
    std::cout << std::setw(15) << "[BitcoinExchange] "
              << "copy!!" << std::endl;
}

BitcoinExchange::~BitcoinExchange() {
    std::cout << std::setw(15) << "[BitcoinExchange] "
              << "delete!!" << std::endl;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &ref) {
    *this = ref;
    std::cout << std::setw(15) << "[BitcoinExchange] "
              << "operator=!!" << std::endl;
    return (*this);
}
