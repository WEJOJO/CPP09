#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <cstdlib>
#include <queue>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>

class BitcoinExchange {
  private:
    std::map<std::string, double> standard;
    std::ifstream myfile;
    std::ifstream stand;
    void MakeMap();
    BitcoinExchange &operator=(const BitcoinExchange &ref);
    BitcoinExchange(const BitcoinExchange &ref);

  public:
    BitcoinExchange();
    ~BitcoinExchange();

    void MakeChange(char *_argv);
    int ValidationCheck(std::string &line_, std::queue<std::string> &_strs);
    bool IsLeapYear(int year);
    bool IsValidDate(int year, int month, int day);
    std::queue<std::string> Split(std::string input, char delimiter);
    std::string ConvertDouble(double value);
};

#endif