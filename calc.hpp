#ifndef CALC_HPP_
#define CALC_HPP_

#include <vector>
#include <set>
#include <string>

namespace Calc {
struct Token {
  // changed val to float
  char type {};
  float val {};
};

std::vector<Token> tokenise(const std::string&);
std::vector<Token> infixToPostfix(const std::vector<Token>&);
float evalPostfix(const std::vector<Token>&);
float eval(const std::string&);

}     // namespace Calc

#endif    // CALC_HPP_
