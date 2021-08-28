#include "lexer/lexer.h"
#include "parser/parser.h"
#include <gtest/gtest.h>

#include <iostream>
#include <string>

namespace
{
TEST(ParserTest, Rel_ExpectedLog) {
   std::vector<std::string> test_text {
      "1+2 < 4",
      "1-2 <= 3+1",
      "3 > 1+2",
      "4*5 >= 1/2"
   };
   for (auto text : test_text) {
      std::cout << "-------- Input Text ---------" << std::endl;
      std::cout << text << std::endl;
      std::istringstream iss(text);
      LBC::Lexer lex(iss);
      auto parser = LBC::Parser(lex);
      std::cout << "-------- Output Text ---------" << std::endl;
      auto node = parser.rel();
      std::cout << node->to_string() << std::endl;
   }
}

TEST(ParserTest, Expr_ExpectedLog) {
   std::vector<std::string> test_text {
      "1+2",
      "1+2*4",
      "1+3-5",
      "9+1*4+3/5-1",
      "1",
      "1+-2",
      "1+!!2",
      "1+!-(!2)",
      "1 + 2 * (5 + 6) + 4"
   };
   for (auto text : test_text) {
      std::cout << "-------- Input Text ---------" << std::endl;
      std::cout << text << std::endl;
      std::istringstream iss(text);
      LBC::Lexer lex(iss);
      auto parser = LBC::Parser(lex);
      std::cout << "-------- Output Text ---------" << std::endl;
      auto node = parser.expr();
      std::cout << node->to_string() << std::endl;
   }
}

TEST(ParserTest, Unary_ExpectedLog) {
   std::vector<std::string> test_text {
      "--1",
      "!!1",
      "-!--!-1"
   };
   for (auto text : test_text) {
      std::cout << "-------- Input Text ---------" << std::endl;
      std::cout << text << std::endl;
      std::istringstream iss(text);
      LBC::Lexer lex(iss);
      auto parser = LBC::Parser(lex);
      std::cout << "-------- Output Text ---------" << std::endl;
      auto node = parser.unary();
      std::cout << node->to_string() << std::endl;
   }
}

}
