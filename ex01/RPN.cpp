#include "RPN.hpp"
////////////////////////////////Orthodox////////////////////////////////
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
    this->my_stack = ref.my_stack;
    std::cout << std::setw(15) << "[RPN] "
              << "operator=!!" << std::endl;
    return (*this);
}
////////////////////////////////Orthodox////////////////////////////////

RPN::RPN(char *argv[]) {
    int i = 1;
    long t1, t2 = 0;
    int token_cnt = 0;
    while (argv[i]) {
        std::stringstream ss(argv[i]);
        std::string token;
        while (ss >> token) {
            if (token.length() > 2) { //-이고 뒤에 숫자인 경우 예외를 둔다
                std::cout << "Error: arg length must <= 2" << std::endl;
                exit(1);
            }
            if (token.length() == 2 &&
                (token[0] != '-' || token[1] < 48 || token[1] > 57)) {
                std::cout << "Error: Operand / Operator Error" << std::endl;
                exit(1);
            }
            if (token.length() == 1 && (token[0] == '*' || token[0] == '+' ||
                                        token[0] == '-' || token[0] == '/')) {
                if (my_stack.size() < 2) {
                    std::cout << "Error: Not Enough Operand Before Operator"
                              << std::endl;
                    exit(1);
                }
                t2 = my_stack.top();
                my_stack.pop();
                t1 = my_stack.top();
                my_stack.pop();
                if (token[0] == '*') {
                    if ((t1 * t2) > INT_MAX || (t1 * t2) < INT_MIN) {
                        std::cout << "Error: Int Overflow" << std::endl;
                        exit(1);
                    }
                    my_stack.push(t1 * t2);
                    token_cnt++;
                    continue;
                } else if (token[0] == '+') {
                    if ((t1 + t2) > INT_MAX || (t1 + t2) < INT_MIN) {
                        std::cout << "Error: Int Overflow" << std::endl;
                        exit(1);
                    }
                    my_stack.push(t1 + t2);
                    token_cnt++;
                    continue;
                } else if (token[0] == '-') {
                    if ((t1 - t2) > INT_MAX || (t1 - t2) < INT_MIN) {
                        std::cout << "Error: Int Overflow" << std::endl;
                        exit(1);
                    }
                    my_stack.push(t1 - t2);
                    token_cnt++;
                    continue;
                } else {
                    if (t2 == 0) {
                        std::cout << "Error: Divided by 0" << std::endl;
                        exit(1);
                    }
                    my_stack.push(t1 / t2);
                    token_cnt++;
                    continue;
                }
            } else {
                if (token[0] == '-' && (token[1] < 48 || token[1] > 57)) {
                    std::cout << "Error: Operand Error" << std::endl;
                    exit(1);
                }
                if (token.length() == 1 && (token[0] < 48 || token[0] > 57)) {
                    std::cout << "Error: Operand Error" << std::endl;
                    exit(1);
                }
                my_stack.push(atoi(token.c_str()));
            }
            token_cnt++;
        }
        i++;
    }
    if (my_stack.size() != 1 || token_cnt == 1) {
        std::cout << "Error: Operand too many" << std::endl;
        exit(1);
    }
    std::cout << my_stack.top() << std::endl;
}
