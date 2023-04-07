#include <cstdlib>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        std::cout << "Error: Need arg" << std::endl;
        exit(1);
    }
    std::stack<int> my_stack;
    int i = 1;
    int t1, t2 = 0;
    while (argv[i]) {
        std::stringstream ss(argv[i]);
        std::string token;
        while (ss >> token) {
            if (token.length() > 2) { //-이고 뒤에 숫자인 경우 예외를 둔다
                std::cout << "Error: arg length must <= 2" << std::endl;
                exit(1);
            }
            if (token.length() == 2 && (token[0]!='-' || token[1] < 48 || token[1] > 57)) {
                std::cout << "Error: Operand / Operator Error" << std::endl;
                exit(1);
            }
            if (token.length() == 1 && (token[0] == '*' || token[0] == '+' || token[0] == '-' ||
                token[0] == '/')) {
                if (my_stack.size() < 2) {
                    std::cout << "Error: Not Enough Operand Before Operator" << std::endl;
                    exit(1);
                }
                t2 = my_stack.top();
                my_stack.pop();
                t1 = my_stack.top();
                my_stack.pop();
                if (token[0] == '*') {
                    my_stack.push(t1 * t2);
                    continue;
                } else if (token[0] == '+') {
                    my_stack.push(t1 + t2);
                    continue;
                } else if (token[0] == '-') {
                    my_stack.push(t1 - t2);
                    continue;
                } else {
                    my_stack.push(t1 / t2);
                    continue;
                }
            } else {
                if (token[0]=='-' && (token[1] < 48 || token[1] > 57))
                {
                    std::cout << "Error: Operand Error" << std::endl;
                    exit(1);
                }
                if (token.length()==1 && (token[0] < 48 || token[0] > 57))
                {
                    std::cout << "Error: Operand Error" << std::endl;
                    exit(1);
                }
                my_stack.push(atoi(token.c_str()));
            }
        }
        i++;
    }
    if (my_stack.size() != 1) {
        std::cout << "Error: Operand too many" << std::endl;
        exit(1);
    }
    std::cout << my_stack.top() << std::endl;
}