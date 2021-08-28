#include "lexer/lexer.h"
#include "parser/parser.h"
#include <gtest/gtest.h>

#include <iostream>
#include <string>

namespace
{
TEST(ParserTest, Boolean_ExpectedLog) {
   std::vector<std::string> test_text {
      "1 && 2 || 3 && 4",
      "1!=2 && 3==4 || 4==5 && 5!=6",
      "0<1 != 2<=3 && 4>5 == 6>=7 || 8+9 == 10/11 && 12-13 != 14*15"
   };
   for (auto text : test_text) {
      std::cout << "-------- Input Text ---------" << std::endl;
      std::cout << text << std::endl;
      std::istringstream iss(text);
      LBC::Lexer lex(iss);
      auto parser = LBC::Parser(lex);
      std::cout << "-------- Output Text ---------" << std::endl;
      auto node = parser.boolean();
      std::cout << node->to_string() << std::endl;
   }
}

TEST(DISABLED_ParserTest, Equality_ExpectedLog) {
   std::vector<std::string> test_text {
      "1+2 != 4",
      "1-2 == 3+1",
      "3 > 1+2 == 2",
      "4*5 >= 1/2 != 4+5"
   };
   for (auto text : test_text) {
      std::cout << "-------- Input Text ---------" << std::endl;
      std::cout << text << std::endl;
      std::istringstream iss(text);
      LBC::Lexer lex(iss);
      auto parser = LBC::Parser(lex);
      std::cout << "-------- Output Text ---------" << std::endl;
      auto node = parser.equality();
      std::cout << node->to_string() << std::endl;
   }
}

TEST(DISABLED_ParserTest, Rel_ExpectedLog) {
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

TEST(DISABLED_ParserTest, Expr_ExpectedLog) {
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

TEST(DISABLED_ParserTest, Unary_ExpectedLog) {
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
