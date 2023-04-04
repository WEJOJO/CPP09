#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

class BitcoinExchange {
  private:
    /* data */

  public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &ref);
    ~BitcoinExchange();

    BitcoinExchange &operator=(const BitcoinExchange &ref);
};

#endif
