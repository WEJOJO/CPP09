#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <deque>
#include <fstream>
#include <map>
#include <sstream>

class BitcoinExchange {
  private:
    std::map<std::string, double> standard;
    std::ifstream myfile;
    std::ifstream stand;
    void  MakeMap();

  public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &ref);
    BitcoinExchange &operator=(const BitcoinExchange &ref);
    ~BitcoinExchange();

    void MakeChange(char *_argv);
    int ValidationCheck(std::string &line_, std::deque<std::string> &_strs);
    bool IsLeapYear(int year);
    bool IsValidDate(int year, int month, int day);
    std::deque<std::string> Split(std::string input, char delimiter);
    std::string ConvertDouble(double value);
};

#endif