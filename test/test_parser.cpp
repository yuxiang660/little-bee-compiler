#include "lexer/lexer.h"
#include "parser/parser.h"
#include <gtest/gtest.h>

#include <iostream>
#include <string>

namespace
{
TEST(ParserTest, Program_ExpectedLog) {
   std::vector<std::string> test_text {
      "{int a; a=1;{int b; b=2;}}"
   };
   for (auto text : test_text) {
      std::cout << "-------- Input Text ---------" << std::endl;
      std::cout << text << std::endl;
      std::istringstream iss(text);
      LBC::Lexer lex(iss);
      auto parser = LBC::Parser(lex);
      std::cout << "-------- Output Text ---------" << std::endl;
      int ret = parser.program();
      EXPECT_EQ(ret, 0);
      parser.dump();
   }
}

TEST(ParserTest, Block_ExpectedLog) {
   std::vector<std::string> test_text {
      "{int a; a = 1+1+2;}"
   };
   for (auto text : test_text) {
      std::cout << "-------- Input Text ---------" << std::endl;
      std::cout << text << std::endl;
      std::istringstream iss(text);
      LBC::Lexer lex(iss);
      auto parser = LBC::Parser(lex);
      std::cout << "-------- Output Text ---------" << std::endl;
      parser.block(0);
      parser.dump();
   }
}

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
      parser.dump();
      std::cout << "\t" << node->to_string() << std::endl;
   }
}

TEST(ParserTest, Equality_ExpectedLog) {
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
      parser.dump();
      std::cout << "\t" << node->to_string() << std::endl;
   }
}

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
      parser.dump();
      std::cout << "\t" << node->to_string() << std::endl;
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
      parser.dump();
      std::cout << "\t" << node->to_string() << std::endl;
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
      parser.dump();
      std::cout << "\t" << node->to_string() << std::endl;
   }
}

}
