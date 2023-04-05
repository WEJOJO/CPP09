#include <iomanip>
#include <iostream>

#include "RPN.hpp"

RPN::RPN() {
    std::cout << std::setw(15) << "[RPN] "
              << "create!!" << std::endl;
}

RPN::RPN(const RPN &ref) {
    *this = ref;
    std::cout << std::setw(15) << "[RPN] "
              << "copy!!" << std::endl;
}

RPN::~RPN() {
    std::cout << std::setw(15) << "[RPN] "
              << "delete!!" << std::endl;
}

RPN &RPN::operator=(const RPN &ref) {
    *this = ref;
    std::cout << std::setw(15) << "[RPN] "
              << "operator=!!" << std::endl;
    return (*this);
}
