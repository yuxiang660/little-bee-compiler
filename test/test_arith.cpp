#include "lexer/lexer.h"
#include "lexer/token.h"
#include <gtest/gtest.h>
#include <iostream>

using namespace LBC;

namespace
{

class ParserAddSud
{
public:
   explicit ParserAddSud(Lexer& l):
      m_lex(l)
   {
      move();
   }

public:
   void expr() {
      term();
      while (true) {
         if (m_look->get_tag() == Tag::OTHER) {
            auto op = m_look->get_lexeme();
            move();
            term();
            std::cout << op;
         }
         else {
            std::cout << std::endl;
            return;
         }
      }
   }

   void term() {
      std::cout << m_look->get_lexeme();
      move();
   }

   void move() {
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
   parser.expr();
}

}
