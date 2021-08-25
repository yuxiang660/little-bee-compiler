#include "lexer/lexer.h"
#include <gtest/gtest.h>

namespace
{

TEST(TestLexer, Scan_ExpectedBehavior) {
   LBC::Lexer l;
   auto token = l.scan();
   std::cout << token->toString() << std::endl;
}

}
