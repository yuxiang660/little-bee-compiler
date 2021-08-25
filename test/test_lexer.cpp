#include "lexer/lexer.h"
#include "lexer/token.h"
#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include <string>

namespace
{

TEST(TestLexer, Scan_ExpectedBehavior) {
   std::string mock_inputs = "if";
   std::istringstream iss(mock_inputs);
   LBC::Lexer l(iss);
   auto token_ptr = l.scan();
   const LBC::TokenInterface& token = *token_ptr;
   std::cout << token.get_lexeme() << std::endl;
   const LBC::Token t = *(std::dynamic_pointer_cast<LBC::Token>(token_ptr));
   std::cout << t.get_lexeme() << std::endl;
}

}
