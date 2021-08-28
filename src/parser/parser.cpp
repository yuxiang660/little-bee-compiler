#include "parser/parser.h"
#include "parser/arith.h"
#include "parser/rel.h"
#include "parser/unary.h"
#include "parser/type.h"
#include "parser/symbol.h"
#include "env/env.h"

#include <cassert>
#include <memory>

namespace LBC
{

Parser::Parser(Lexer& l, std::ostream& out):
   m_lex(l),
   m_out(out),
   m_cur_env(nullptr),
   m_look(m_lex.scan())
{
}

NodePtr Parser::block() {
   move_ahead(1, Tag::LBRACE);
   EnvPtr saved_env = m_cur_env;
   m_cur_env = std::make_shared<Env>(m_cur_env);
   NodePtr node = stmts();
   move_ahead(1, Tag::RBRACE);
   m_cur_env = saved_env;
   return node;
}

static bool is_type_tag(Tag t) {
   return (t == Tag::INT  || t == Tag::FLOAT || t == Tag::BOOL || t == Tag::CHAR);
}

void Parser::decls() {
   while (is_type_tag(m_look->get_tag())) {
      Type type = Node::get_tag_type(m_look->get_tag());
      move_ahead(4, Tag::INT, Tag::FLOAT, Tag::BOOL, Tag::CHAR);
      while (true) {
         if (m_cur_env->is_redefine(m_look)) {
            std::ostringstream oss;
            oss << m_look->get_lexeme() << " is redefined in this scope" << std::endl;
            throw Exception(ERR_PARSER_REDEFINE, oss.str().c_str());
         }
         NodePtr symbol = std::make_shared<SymbolNode>(m_look->get_lexeme().c_str(), type);
         m_cur_env->put(m_look, symbol);
         move_ahead(1, Tag::SYMBOL);
         if (m_look->get_tag() == Tag::SEMI) {
            move_ahead(1, Tag::SEMI);
            break;
         }
         else {
            move_ahead(1, Tag::COMMA);
         }
      }
   }
}

NodePtr Parser::stmts() {
   if (is_type_tag(m_look->get_tag())) decls();
   return assign();
}

NodePtr Parser::assign() {
   if (m_look->get_tag() == Tag::SYMBOL) {
      auto symbol = m_cur_env->get(m_look);
      if (symbol.get() == nullptr) {
         std::ostringstream oss;
         oss << m_look->get_lexeme() << " is not defined" << std::endl;
         throw Exception(ERR_PARSER_NODEFINE, oss.str().c_str());
      }
      move_ahead(1, Tag::SYMBOL);
      if (m_look->get_tag() == Tag::ASSIGN) {
         auto op = Node::make_node(m_look);
         move_ahead(1, Tag::ASSIGN);
         auto node = boolean();
         m_out << '\t' << symbol->to_string() << " " << op->to_string() << " " << node->to_string() << std::endl;
         move_ahead(1, Tag::SEMI);
         return nullptr;
      }
   }
   return boolean();
}

NodePtr Parser::boolean() {
   auto node = join();
   while (m_look->get_tag() == Tag::OR) {
      auto op = Node::make_node(m_look);
      move_ahead(1, Tag::OR);
      node = RelGen(op, node, join()).program(m_out);
   }
   return node;
}

NodePtr Parser::join() {
   auto node = equality();
   while (m_look->get_tag() == Tag::AND) {
      auto op = Node::make_node(m_look);
      move_ahead(1, Tag::AND);
      node = RelGen(op, node, equality()).program(m_out);
   }
   return node;
}

NodePtr Parser::equality() {
   auto node = rel();
   if (m_look->get_tag() == Tag::EQ || m_look->get_tag() == Tag::NE) {
      auto op = Node::make_node(m_look);
      move_ahead(2, Tag::EQ, Tag::NE);
      node = RelGen(op, node, rel()).program(m_out);
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
      move_ahead(4, Tag::LESS, Tag::LE, Tag::GREAT, Tag::GE);
      return RelGen(op, node, expr()).program(m_out);
   }
   default:
      return node;
   }
}

NodePtr Parser::expr() {
   auto node = term();
   while (m_look->get_tag() == Tag::ADD || m_look->get_tag() == Tag::SUB) {
      auto op = Node::make_node(m_look);
      move_ahead(2, Tag::ADD, Tag::SUB);
      node = ArithGen(op, node, term()).program(m_out);
   }
   return node;
}

NodePtr Parser::term() {
   auto node = unary();
   while (m_look->get_tag() == Tag::MUL || m_look->get_tag() == Tag::DIV) {
      auto op =  Node::make_node(m_look);
      move_ahead(2, Tag::MUL, Tag::DIV);
      node = ArithGen(op, node, unary()).program(m_out);
   }
   return node;
}

NodePtr Parser::unary() {
   if (m_look->get_tag() == Tag::SUB /* Take SUB as MINUX here */) {
      move_ahead(1, Tag::SUB);
      return UnaryGen(Tag::MINUS, unary()).program(m_out);
   }
   else if (m_look->get_tag() == Tag::NOT) {
      move_ahead(1, Tag::NOT);
      return UnaryGen(Tag::NOT, unary()).program(m_out);
   }
   return factor();
}

NodePtr Parser::factor() {
   if (m_look->get_tag() == Tag::INTEGER) {
      auto node = Node::make_node(m_look);
      move_ahead(1, Tag::INTEGER);
      return node;
   }

   if (m_look->get_tag() == Tag::REAL) {
      auto node =  Node::make_node(m_look);
      move_ahead(1, Tag::REAL);
      return node;
   }

   if (m_look->get_tag() == Tag::LBRACKET) {
      move_ahead(1, Tag::LBRACKET);
      auto node = expr();
      move_ahead(1, Tag::RBRACKET);
      return node;
   }

   std::ostringstream oss;
   oss << "Unexpected token in the expression: " << m_look->get_lexeme() << std::endl;
   throw Exception(ERR_PARSER_UNEXPECTED_TOKEN, oss.str().c_str());
   return nullptr;
}

void Parser::move_ahead(int count, ...) {
   bool is_move_ahead = false;

   std::va_list args;
   va_start(args, count);
   for (int i = 0; i < count; ++i) {
      Tag expected_tag = va_arg(args, Tag);
      if (m_look->get_tag() == expected_tag) {
         is_move_ahead = true;
         break;
      }
   }
   va_end(args);

   if (!is_move_ahead) {
      std::ostringstream oss;
      oss << "Unexpected token: " << m_look->get_lexeme() << std::endl;
      throw Exception(ERR_PARSER_UNEXPECTED_TOKEN, oss.str().c_str());
   }

   m_look = m_lex.scan();
}

}

