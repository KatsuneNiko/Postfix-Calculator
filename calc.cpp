#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <string>
#include <algorithm>
#include <cmath>
#include "calc.hpp"

// method for returning the operand precedence to be used in the algorithm
// added support for exponent operand, which has a higher priority than other operands
int operand_precedence(char type){
  if (type == '^'){
    return 3;
  }
  else if (type == '/' || type == '*')
    return 2;
  else if (type == '+' || type == '-')
    return 1;
  else
    return -1;
}

std::vector<Calc::Token> Calc::infixToPostfix(const std::vector<Token>& input) {
  std::vector<Calc::Token> output;
  std::stack<Calc::Token> operator_stack;

  for(Token token : input){
    if (token.type == 'n'){
      output.push_back(token);
    }
    else if (token.type == '('){
      operator_stack.push(token);
    }
    else if (token.type == ')'){
      while(operator_stack.top().type != '('){
        output.push_back(operator_stack.top());
        operator_stack.pop();
      }
      operator_stack.pop();
    }
    else{
      // while the stack isn't empty and the top operand in stack isn't a left parenthesis
      // and the precedence of the operator on top of stack is either greater than the precedence of the token
      // or it has the same precedence and is a left-associative operator (not ^)
      // push to output and pop stack
      while(!operator_stack.empty() && operator_stack.top().type != '(' && 
            (operand_precedence(operator_stack.top().type) > operand_precedence(token.type) ||
            (operand_precedence(operator_stack.top().type) == operand_precedence(token.type) && token.type != '^'))){
        output.push_back(operator_stack.top());
        operator_stack.pop();
      }
      operator_stack.push(token);
    }
  }

  // process all operators remaining on the stack
  while(!operator_stack.empty()){
      output.push_back(operator_stack.top());
      operator_stack.pop();
  }

  // debug prints
  // std::cout << "The size of output is currently " << output.size() << "\n";
  // for(Token token : output){
  //   if(token.type == 'n'){
  //     std::cout << token.val << " ";
  //   }
  //   else{
  //     std::cout << token.type << " ";
  //   }
  // }
  // std::cout << "\n";

  return output;
}

// changed return type and type of stack and val to float
float Calc::evalPostfix(const std::vector<Token>& tokens) {
  if (tokens.empty()) {
    return 0;
  }
  std::vector<float> stack;
  for (Token t : tokens) {
    if (t.type == 'n') {
      stack.push_back(t.val);
    } else {
      float val = 0;
      if (t.type == '+') {
        val = stack.back() + *(stack.end()-2);
      } else if (t.type == '*') {
        val = stack.back() * *(stack.end()-2);
      } else if (t.type == '-') {
        val = *(stack.end()-2) - stack.back();
      } else if (t.type == '/') {
        if (stack.back() == 0) {
          throw std::runtime_error("divide by zero");
        }
        val = *(stack.end()-2) / stack.back();
      } else if (t.type == '^'){
        // evaluate using the pow() function from cmath library
        val = pow(*(stack.end()-2), stack.back());
      } else {
          std::cout << "invalid token\n";
      }
      stack.pop_back();
      stack.pop_back();
      stack.push_back(val);
    }
  }
  return stack.back();
}

std::vector<Calc::Token> Calc::tokenise(const std::string& expression) {
  // added ^ to list of operands
  const std::vector<char> symbols = {'+', '-', '*', '/', '(', ')', '^'};
  std::vector<Token> tokens {};
  // bool for if there's already a floating point
  bool floating_point;

  for (std::size_t i =0; i < expression.size(); ++i) {
    const char c = expression[i];
    // check if c is one of '+', '-', '*', '/', '(', ')' or '^'
    if (std::find(symbols.begin(), symbols.end(), c) != symbols.end()) {
      tokens.push_back({c});
    } else if (isdigit(c)) {
      // process multiple digit integers
      floating_point = false;
      std::string num {c};
      // check if the next digit is a number or a floating point
      while (i + 1 < expression.size() && (isdigit(expression[i + 1]) || expression[i + 1] == '.')) {
        ++i;
        // if there isn't a floating point already, set it to true
        if (c == '.' && !floating_point){
          floating_point = true;
        }
        // if there's two floating points in the same number, return error
        else if (c == '.' && floating_point) {
          throw std::runtime_error("floating point formatting incorrect");
        }
        num.push_back(expression[i]);
      }
      tokens.push_back({'n', std::stof(num)});
    }
  }
  return tokens;
}

// changed to float
float Calc::eval(const std::string& expression) {
  std::vector<Token> tokens = tokenise(expression);
  std::vector<Token> postfix = infixToPostfix(tokens);
  return evalPostfix(postfix);
}
