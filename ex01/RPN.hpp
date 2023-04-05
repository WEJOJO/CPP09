#ifndef RPN_HPP
#define RPN_HPP

#include <stack>

class RPN {
  private:
    std::stack<int> _stack;

  public:
    RPN();
    RPN(const RPN &ref);
    ~RPN();
    RPN &operator=(const RPN &ref);
    void Calculator(char *_arg);
};

#endif
