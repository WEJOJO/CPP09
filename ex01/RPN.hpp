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
    RPN(const RPN &ref);
    RPN &operator=(const RPN &ref);

  public:
    RPN(char *argv[]);
    ~RPN();
};

#endif
