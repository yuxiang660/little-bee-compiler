#include "lexer/lexer.h"
#include "lexer/token.h"
#include "lexer/temp.h"
#include "internal/error.h"
#include <gtest/gtest.h>

#include <cstdarg>
#include <memory>
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
      // expr   -> term + expr
      //         | term - expr
      //         | term
      // term   -> factor * expr
      //         | factor / expr
      //         | factor
      // factor -> digital
      expr();
   }

private:
   TokenPtr expr() {
      auto node = term();
      while (m_look->get_tag() == Tag::ADD || m_look->get_tag() == Tag::SUB) {
         auto op = m_look;
         match(2, Tag::ADD, Tag::SUB);
         node = arith(op, node, term());
      }
      return node;
   }

   TokenPtr term() {
      auto node = factor();
      while (m_look->get_tag() == Tag::MUL || m_look->get_tag() == Tag::DIV) {
         auto op = m_look;
         match(2, Tag::MUL, Tag::DIV);
         node = arith(op, node, factor());
      }
      return node;
   }

   TokenPtr factor() {
      auto node = m_look;
      match(2, Tag::INTEGER, Tag::REAL);
      return node;
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

   TokenPtr arith(const TokenPtr& op, const TokenPtr& l_operand, const TokenPtr& r_operand) {
      auto node = std::make_shared<Temp>();
      std::cout << node->get_lexeme() << " = " << l_operand->get_lexeme() << " " << op->get_lexeme()
                << " " << r_operand->get_lexeme() << std::endl;
      return node;
   }

private:
   Lexer& m_lex;
   TokenPtr m_look;
};

TEST(TestAddSud, ExpectedLog) {
   std::string text = "1+2*5+7";
   std::istringstream iss(text);
   LBC::Lexer lex(iss);
   ParserAddSud parser = ParserAddSud(lex);
   parser.prog();
}

}
