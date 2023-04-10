#include "RPN.hpp"

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        std::cout << "Error: Need arg" << std::endl;
        exit(1);
    }
    RPN my_rpn(argv);
}