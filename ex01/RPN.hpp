#ifndef RPN_HPP
#define RPN_HPP

#include <cstdlib>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <iomanip>

class RPN {
  private:
    std::stack<int> my_stack;
    RPN();

  public:
    RPN(char *argv[]);
    RPN(const RPN &ref);
    ~RPN();
    RPN &operator=(const RPN &ref);
};

#endif
