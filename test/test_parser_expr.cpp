#include "lexer/lexer.h"
#include "lexer/token.h"
#include "parser/node.h"
#include "parser/arith.h"
#include "internal/error.h"
#include <gtest/gtest.h>

#include <cassert>
#include <cstdarg>
#include <memory>
#include <iostream>
#include <sstream>
#include <typeinfo>


using namespace LBC;

namespace
{

class ParserExpr
{
public:
   explicit ParserExpr(Lexer& l, std::ostream& out = std::cout):
      m_lex(l),
      m_out(out),
      m_look(m_lex.scan())
   {
   }

public:
   void prog() {
      /*
       * expr   -> term t_rest
       * t_rest -> + term t_rest
       *         | - term t_rest
       *         | term
       *         | ε
       * term   -> factor f_rest
       * f_rest -> * factor f_rest
       *         | / factor f_rest
       *         | factor
       *         | ε
       * factor -> digital
      */
      auto node = expr();
      m_out << node->to_string() << std::endl;
   }

private:
   NodePtr expr() {
      auto node = term();
      while (m_look->get_tag() == Tag::ADD || m_look->get_tag() == Tag::SUB) {
         auto op = NodeFactory::make_node(m_look);
         match(2, Tag::ADD, Tag::SUB);
         node = ArithGen(op, node, term(), m_out).program();
      }
      return node;
   }

   NodePtr term() {
      auto node = factor();
      while (m_look->get_tag() == Tag::MUL || m_look->get_tag() == Tag::DIV) {
         auto op =  NodeFactory::make_node(m_look);
         match(2, Tag::MUL, Tag::DIV);
         node = ArithGen(op, node, factor(), m_out).program();
      }
      return node;
   }

   NodePtr factor() {
      auto node =  NodeFactory::make_node(m_look);
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

private:
   Lexer& m_lex;
   std::ostream& m_out;
   TokenPtr m_look;
};

TEST(ParserExprTest, ExpectedLog) {
   std::vector<std::string> test_text {
      "1+2",
      "1+2*4",
      "1+3-5",
      "9+1*4+3/5-1",
      "9+1*4/3/5-1"
   };
   for (auto text : test_text) {
      std::cout << "-------- Input Text ---------" << std::endl;
      std::cout << text << std::endl;
      std::istringstream iss(text);
      LBC::Lexer lex(iss);
      ParserExpr parser = ParserExpr(lex);
      std::cout << "-------- Output Text ---------" << std::endl;
      parser.prog();
   }
}

}
