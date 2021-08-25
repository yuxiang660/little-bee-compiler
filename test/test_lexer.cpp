#include "lexer/lexer.h"
#include "lexer/token.h"
#include <gtest/gtest.h>

namespace
{

TEST(TestLexer, Scan_ExpectedBehavior) {
   LBC::Lexer l;
   auto token_ptr = l.scan();
   const LBC::TokenInterface& token = *token_ptr;
   std::cout << token.get_lexeme() << std::endl;
}

}
