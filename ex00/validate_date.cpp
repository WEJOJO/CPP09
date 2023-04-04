#include <iostream>
#include <sstream>

bool isLeapYear(int year) {
    return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}

bool isValidDate(int year, int month, int day) {
    if (month < 1 || month > 12)
        return false;
    if (day < 1 || day > 31)
        return false;

    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30)
            return false;
    } else if (month == 2) {
        if (isLeapYear(year) && day > 29)
            return false;
        if (!isLeapYear(year) && day > 28)
            return false;
    }

    return true;
}

int main() {
    std::string input;
    std::getline(std::cin, input);
    std::istringstream iss(input);

    int year, month, day;
    char delimiter;

    if (iss >> year >> delimiter >> month >> delimiter >> day) {
        if (isValidDate(year, month, day)) {
            std::cout << "Valid date" << std::endl;
        } else {
            std::cout << "Invalid date" << std::endl;
        }
    } else {
        std::cout << "Invalid input format" << std::endl;
    }

    return 0;
}
