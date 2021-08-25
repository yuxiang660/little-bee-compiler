#include "lexer/num.h"
#include "lexer/tag.h"
#include <gtest/gtest.h>

#include <iostream>

namespace
{

TEST(TestNum, ToString_Int_ExpectedTagAndString) {
   LBC::Integer i(11);
   std::cout << i.toString() << std::endl;
   EXPECT_EQ(i.get_tag(), LBC::Tag::INTEGER);
}

TEST(TestNum, ToString_Float_ExpectedTagAndString) {
   LBC::Float f(11.22);
   std::cout << f.toString() << std::endl;
   EXPECT_EQ(f.get_tag(), LBC::Tag::REAL);
}

}
