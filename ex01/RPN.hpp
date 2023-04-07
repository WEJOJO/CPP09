#ifndef RPN_HPP
#define RPN_HPP

#include <cstdlib>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>

class RPN {
  private:
    std::stack<int> my_stack;

  public:
    RPN();
    RPN(const RPN &ref);
    ~RPN();
    RPN &operator=(const RPN &ref);
    void Calculator(char *_arg);
};

#endif
