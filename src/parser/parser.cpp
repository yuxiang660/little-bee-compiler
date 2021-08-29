#include "parser/parser.h"
#include "parser/arith.h"
#include "parser/rel.h"
#include "parser/unary.h"
#include "parser/type.h"
#include "parser/symbol.h"
#include "parser/assign.h"
#include "parser/stmt.h"
#include "env/env.h"

#include <cassert>
#include <memory>

namespace LBC
{

Parser::Parser(Lexer& l):
   m_lex(l),
   m_cur_env(nullptr),
   m_look(m_lex.scan())
{
}

void Parser::dump(std::ostream& out)
{
   out << m_out.str() << std::endl;
}

int Parser::program() {
   try {
      block(Stmt::gen_unique_label(), true);
   }
   catch(const Exception& e) {
      std::cerr << e.what() << std::endl;
      return e.code();
   }
   return 0;
}

static bool is_type_tag(Tag t) {
   return (t == Tag::INT  || t == Tag::FLOAT || t == Tag::BOOL || t == Tag::CHAR);
}

int Parser::block(int begin_label, bool is_outermost) {
   int next_label = begin_label;

   move_ahead(1, Tag::LBRACE);

   EnvPtr saved_env = m_cur_env;
   m_cur_env = std::make_shared<Env>(m_cur_env);
   decls();
   next_label = stmts(next_label);
   m_cur_env = saved_env;

   if (!is_outermost) {
      move_ahead(1, Tag::RBRACE);
      return next_label;
   }

   // Stop scanning since the block is outermost
   if (m_look->get_tag() != Tag::RBRACE)
      throw Exception(ERR_PARSER_UNEXPECTED_TOKEN, m_look->err_message().c_str());

   return next_label;
}

void Parser::decls() {
   while (is_type_tag(m_look->get_tag())) {
      Type type = Node::get_tag_type(m_look->get_tag());
      move_ahead(4, Tag::INT, Tag::FLOAT, Tag::BOOL, Tag::CHAR);
      while (true) {
         NodePtr symbol = std::make_shared<SymbolNode>(m_look->get_lexeme().c_str(), type);
         if (m_cur_env->is_redefine(m_look)) {
            throw Exception(ERR_PARSER_REDEFINE, m_look->err_message().c_str());
         }

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

int Parser::stmts(int begin_label) {
   int next_label = begin_label;

   bool end = false;
   while (!end) {
      // one statement
      switch (m_look->get_tag())
      {
      case Tag::SEMI:
      {
         move_ahead(1, Tag::SEMI);
         break;
      }
      case Tag::LBRACE:
      {
         next_label = block(next_label);
         break;
      }
      case Tag::RBRACE:
      {
         end = true;
         break;
      }
      case Tag::SYMBOL:
      {
         next_label = assign(next_label);
         break;
      }
      default:
      {
         throw Exception(ERR_PARSER_UNEXPECTED_TOKEN, m_look->err_message().c_str());
         break;
      }
      }
   }

   return next_label;
}

int Parser::assign(int begin_label) {
   auto symbol = m_cur_env->get(m_look);
   if (symbol.get() == nullptr) {
      throw Exception(ERR_PARSER_NODEFINE, m_look->err_message().c_str());
   }
   move_ahead(1, Tag::SYMBOL);

   auto op = Node::make_node(m_look);
   move_ahead(1, Tag::ASSIGN);
   auto node = boolean();
   int next_label = Assign(begin_label, symbol, node).prog_stmt(m_out);
   move_ahead(1, Tag::SEMI);

   return next_label;
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
      auto node = boolean();
      move_ahead(1, Tag::RBRACKET);
      return node;
   }

   throw Exception(ERR_PARSER_UNEXPECTED_TOKEN, m_look->err_message().c_str());
   return nullptr;
}

void Parser::move_ahead(int count, ...) {
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
      throw Exception(ERR_PARSER_UNEXPECTED_TOKEN, m_look->err_message().c_str());
   }

   m_look = m_lex.scan();
}

}

