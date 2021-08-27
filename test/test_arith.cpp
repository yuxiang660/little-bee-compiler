#include "lexer/lexer.h"
#include "lexer/token.h"
#include "parser/node.h"
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

class GenInterface
{
public:
   virtual ~GenInterface() = default;
};

class Gen: public GenInterface
{
public:
   explicit Gen(std::ostream& out):
      m_out(out)
   {}

protected:
   std::ostream& m_out;
};

class ArithGen: public Gen
{
public:
   ArithGen(NodePtr op, NodePtr lhs, NodePtr rhs, std::ostream& out):
      Gen(out),
      m_op(op),
      m_lhs(lhs),
      m_rhs(rhs)
   {}

   NodePtr program()
   {
      return NodeFactory::make_arith_node(m_op, gen_arith_code(m_lhs), gen_arith_code(m_rhs));
   }

private:
   NodePtr gen_arith_code(NodePtr node) {
      if (typeid(*node.get()) == typeid(ArithNode)) {
         auto temp_node = NodeFactory::make_temp_node();
         m_out << temp_node->to_string() << " = " << node->to_string() << std::endl;
         return temp_node;
      }

      return node;
   }

private:
   NodePtr m_op;
   NodePtr m_lhs;
   NodePtr m_rhs;
};

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

   NodePtr arith(NodePtr op, NodePtr lhs, NodePtr rhs) {
      if (typeid(*lhs.get()) == typeid(Node) && typeid(*rhs.get()) == typeid(Node)) {
         return NodeFactory::make_arith_node(op, lhs, rhs);
      }

      if (typeid(*lhs.get()) == typeid(ArithNode) && typeid(*rhs.get()) == typeid(ArithNode)) {
         auto l_node = NodeFactory::make_temp_node();
         m_out << l_node->to_string() << " = " << lhs->to_string() << std::endl;
         auto r_node = NodeFactory::make_temp_node();
         m_out << r_node->to_string() << " = " << rhs->to_string() << std::endl;

         return NodeFactory::make_arith_node(op, l_node, r_node);
      }

      if (typeid(*lhs.get()) == typeid(ArithNode)) {
         auto node = NodeFactory::make_temp_node();
         m_out << node->to_string() << " = " << lhs->to_string() << std::endl;

         return NodeFactory::make_arith_node(op, node, rhs);
      }

      assert(typeid(*rhs.get()) == typeid(ArithNode));
      auto node = NodeFactory::make_temp_node();
      m_out << node->to_string() << " = " << rhs->to_string() << std::endl;

      return NodeFactory::make_arith_node(op, lhs, node);
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
