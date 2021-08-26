#include "lexer/lexer.h"
#include "lexer/token.h"
#include "internal/error.h"
#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include <string>

namespace
{

struct LexerTestCase
{
   const char* text;
   LBC::Tag expected_tag;
   const char* expected_lexeme;
};

LexerTestCase lexer_test_cases[] = {
   { "if",       LBC::Tag::IF,       "if"       },
   { "else",     LBC::Tag::ELSE,     "else"     },
   { "while",    LBC::Tag::WHILE,    "while"    },
   { "do",       LBC::Tag::DO,       "do"       },
   { "break",    LBC::Tag::BREAK,    "break"    },
   { "continue", LBC::Tag::CONTINUE, "continue" },
   { "true",     LBC::Tag::TRUE,     "true"     },
   { "false",    LBC::Tag::FALSE,    "false"    },
   { "&&",       LBC::Tag::AND,      "&&"       },
   { "||",       LBC::Tag::OR,       "||"       },
   { "==",       LBC::Tag::EQ,       "=="       },
   { "!=",       LBC::Tag::NE,       "!="       },
   { "<=",       LBC::Tag::LE,       "<="       },
   { ">=",       LBC::Tag::GE,       ">="       },
   { "+",        LBC::Tag::ADD,      "+"        },
   { "-",        LBC::Tag::SUB,      "-"        },
   { "*",        LBC::Tag::MUL,      "*"        },
   { "/",        LBC::Tag::DIV,      "/"        },
   { "!",        LBC::Tag::NOT,      "!"        },
   { "=",        LBC::Tag::ASSIGN,   "="        },
   { ">",        LBC::Tag::GREAT,    ">"        },
   { "<",        LBC::Tag::LESS,     "<"        },
   { "&",        LBC::Tag::BITAND,   "&"        },
   { "|",        LBC::Tag::BITOR,    "|"        },
   { "]",        LBC::Tag::RINDEX,   "]"        },
   { "[",        LBC::Tag::LINDEX,   "["        },
   { "(",        LBC::Tag::LBRACK,   "("        },
   { ")",        LBC::Tag::RBRACK,   ")"        },
   { "int",      LBC::Tag::BASIC,    "int"      },
   { "float",    LBC::Tag::BASIC,    "float"    },
   { "bool",     LBC::Tag::BASIC,    "bool"     },
   { "char",     LBC::Tag::BASIC,    "char"     },
   { "var",      LBC::Tag::SYMBOL,   "var"      },
   { "0123",     LBC::Tag::INTEGER,  "123"      },
   { "0.123",    LBC::Tag::REAL,     "0.123"    }
};

struct LexerTest : public testing::TestWithParam<LexerTestCase> {};
INSTANTIATE_TEST_SUITE_P(LexerTest, LexerTest, ::testing::ValuesIn(lexer_test_cases));

TEST_P(LexerTest, Scan_MockText_ExpectedTagAndLexeme) {
   auto testCase = GetParam();
   std::string mock_text = testCase.text;
   std::istringstream iss(mock_text);
   LBC::Lexer lexer(iss);

   auto token = lexer.scan();
   EXPECT_EQ(testCase.expected_tag, token->get_tag());
   EXPECT_STREQ(testCase.expected_lexeme, token->get_lexeme().c_str());
}

TEST(LexerErrorTest, Scan_InvalidToken_DEATH) {
   std::string invalid_text = "@";
   std::istringstream iss(invalid_text);
   LBC::Lexer lexer(iss);
   EXPECT_THROW(lexer.scan(), LBC::Exception);
}

}
