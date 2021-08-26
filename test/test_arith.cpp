#include "lexer/lexer.h"
#include "lexer/token.h"
#include "internal/error.h"
#include <gtest/gtest.h>

#include <cstdarg>
#include <iostream>
#include <sstream>


using namespace LBC;

namespace
{

class ParserAddSud
{
public:
   explicit ParserAddSud(Lexer& l):
      m_lex(l),
      m_look(m_lex.scan())
   {
   }

public:
   void prog() {
      // expr -> term + expr
      //       | term - expr
      //       | term
      // term -> digital
      expr();
   }

private:
   void expr() {
      term();
      while (m_look->get_tag() == Tag::ADD || m_look->get_tag() == Tag::SUB) {
         auto op_lexeme = m_look->get_lexeme();
         match(2, Tag::ADD, Tag::SUB);
         term();
         std::cout << op_lexeme;
      }
      std::cout << std::endl;
      return;
   }

   void term() {
      std::cout << m_look->get_lexeme();
      match(2, Tag::INTEGER, Tag::REAL);
      return;
   }

   void match(int count, ...) {
      bool is_match = false;

      std::va_list args;
      va_start(args, count);
      for (int i = 0; i < count; ++i) {
         Tag expected_tag = va_arg(args, Tag);
         if (m_look->get_tag() == expected_tag) {
            is_match = true;
            break;
         }
      }
      va_end(args);

      if (!is_match) {
         std::ostringstream oss;
         oss << "Unexpected token: " << m_look->get_lexeme() << std::endl;
         throw Exception(ERR_PARSER_UNEXPECTED_TOKEN, oss.str().c_str());
      }

      m_look = m_lex.scan();
   }

private:
   Lexer& m_lex;
   TokenPtr m_look;
};

TEST(TestAddSud, ExpectedLog) {
   std::string text = "1+2-5+7";
   std::istringstream iss(text);
   LBC::Lexer lex(iss);
   ParserAddSud parser = ParserAddSud(lex);
   parser.prog();
}

}
