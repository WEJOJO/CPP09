#include "BitcoinExchange.hpp"

int main(int argc, char *argv[]) {
    int j = 1;
    if (argc == 1)
    {
        std::cout << "Need File Name" << std::endl;
        exit(1);
    }

    BitcoinExchange coin_change;
    while(argv[j])
    {
        coin_change.MakeChange(argv[j]);
        j++;
    }
}
