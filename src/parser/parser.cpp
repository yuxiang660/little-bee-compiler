#include "parser/parser.h"
#include "parser/arith.h"
#include "parser/rel.h"
#include "parser/unary.h"

#include <cassert>

namespace LBC
{

Parser::Parser(Lexer& l, std::ostream& out):
   m_lex(l),
   m_out(out),
   m_look(m_lex.scan())
{
}

NodePtr Parser::equality() {
   auto node = rel();
   if (m_look->get_tag() == Tag::EQ || m_look->get_tag() == Tag::NE) {
      auto op = Node::make_node(m_look);
      match(2, Tag::EQ, Tag::NE);
      //node = EqGen(op, node, rel(), m_out).program();
   }
   return node;
}

NodePtr Parser::rel() {
   auto node = expr();
   // "<, <=, >, >="
   switch (m_look->get_tag())
   {
   case Tag::LESS:
   case Tag::LE:
   case Tag::GREAT:
   case Tag::GE:
   {
      auto op = Node::make_node(m_look);
      match(4, Tag::LESS, Tag::LE, Tag::GREAT, Tag::GE);
      return RelGen(op, node, expr(), m_out).program();
   }
   default:
      return node;
   }
}

NodePtr Parser::expr() {
   auto node = term();
   while (m_look->get_tag() == Tag::ADD || m_look->get_tag() == Tag::SUB) {
      auto op = Node::make_node(m_look);
      match(2, Tag::ADD, Tag::SUB);
      node = ArithGen(op, node, term(), m_out).program();
   }
   return node;
}

NodePtr Parser::term() {
   auto node = unary();
   while (m_look->get_tag() == Tag::MUL || m_look->get_tag() == Tag::DIV) {
      auto op =  Node::make_node(m_look);
      match(2, Tag::MUL, Tag::DIV);
      node = ArithGen(op, node, unary(), m_out).program();
   }
   return node;
}

NodePtr Parser::unary() {
   if (m_look->get_tag() == Tag::SUB /* Take SUB as MINUX here */) {
      match(1, Tag::SUB);
      return UnaryGen(Tag::MINUS, unary(), m_out).program();
   }
   else if (m_look->get_tag() == Tag::NOT) {
      match(1, Tag::NOT);
      return UnaryGen(Tag::NOT, unary(), m_out).program();
   }
   return factor();
}

NodePtr Parser::factor() {
   if (m_look->get_tag() == Tag::INTEGER) {
      auto node = Node::make_node(m_look, Type::INT);
      match(1, Tag::INTEGER);
      return node;
   }

   if (m_look->get_tag() == Tag::REAL) {
      auto node =  Node::make_node(m_look, Type::FLOAT);
      match(1, Tag::REAL);
      return node;
   }

   if (m_look->get_tag() == Tag::LBRACKET) {
      match(1, Tag::LBRACKET);
      auto node = expr();
      match(1, Tag::RBRACKET);
      return node;
   }

   std::ostringstream oss;
   oss << "Unexpected token in the expression: " << m_look->get_lexeme() << std::endl;
   throw Exception(ERR_PARSER_UNEXPECTED_TOKEN, oss.str().c_str());
   return nullptr;
}

void Parser::match(int count, ...) {
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

}

