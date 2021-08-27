#include "lexer/num.h"
#include "lexer/tag.h"
#include <gtest/gtest.h>

#include <iostream>

namespace
{

TEST(TestNum, ToString_Int_ExpectedTagAndString) {
   LBC::Integer i("11");
   std::cout << i.get_lexeme() << std::endl;
   EXPECT_STREQ("11", i.get_lexeme().c_str());
   EXPECT_EQ(i.get_tag(), LBC::Tag::INTEGER);
   EXPECT_EQ(i.get_val(), 11);
}

TEST(TestNum, ToString_Float_ExpectedTagAndString) {
   LBC::Float f("11.220");
   EXPECT_STREQ("11.220", f.get_lexeme().c_str());
   EXPECT_EQ(f.get_tag(), LBC::Tag::REAL);
   EXPECT_FLOAT_EQ(f.get_val(), 11.22);
}

}
