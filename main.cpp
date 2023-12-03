#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "calc.hpp"

TEST(Calc, addTwoNumbers) {
  std::string input {"3 +5"};
  EXPECT_EQ(Calc::eval(input), 8);
}

// write your own test cases to demonstrate the 
// added functionality

TEST(Calc, exponentTwoNumbers) {
  // testing if exponent works
  std::string input {"3 ^ 5"};
  EXPECT_EQ(Calc::eval(input), 243);
}

TEST(Calc, exponentThreeNumbers) {
  // testing if right associative works
  // if it doesn't work, it'd be (2^3)^2 = 8^2 = 64
  // rather than 2^(3^2) = 2 ^ 9 = 512
  std::string input {"2 ^ 3 ^ 2"};
  EXPECT_EQ(Calc::eval(input), 512);
}

TEST(Calc, floatingPointTest) {
  // testing if floating points are read in correctly
  std::string input {"2.5"};
  EXPECT_FLOAT_EQ(Calc::eval(input), 2.5);
}

TEST(Calc, addTwoFloats) {
  // testing if floating point addition works correctly
  std::string input {"5.1 + 0.55"};
  EXPECT_FLOAT_EQ(Calc::eval(input), 5.65);
}

TEST(Calc, multiplyTwoFloats) {
  // testing if floating point multiplication works correctly
  std::string input {"3.2 * 5.1"};
  EXPECT_FLOAT_EQ(Calc::eval(input), 16.32);
}

TEST(Calc, multiplyAndAdditionWithFloats) {
  // testing if floating point multiplication and addition both work correctly
  std::string input {"3.2 * 5.1 + 0.55"};
  EXPECT_FLOAT_EQ(Calc::eval(input), 16.87);
}

TEST(Calc, exponentsWithFloats) {
  // testing if floating points work with exponentials added earlier
  std::string input {"3.2 ^ 5.1"};
  EXPECT_FLOAT_EQ(Calc::eval(input), 376.93363218793);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
