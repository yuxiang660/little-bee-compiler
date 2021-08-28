#include "parser/node.h"

namespace LBC
{

NodePtr Node::make_node(TokenPtr token)
{
   return std::make_shared<Node>(token, get_tag_type(token->get_tag()));
}

Type Node::get_tag_type(Tag t)
{
   switch (t)
   {
   case Tag::INT:
   case Tag::INTEGER:
      return Type::INT;
   case Tag::FLOAT:
   case Tag::REAL:
      return Type::FLOAT;
   case Tag::CHAR:
      return Type::CHAR;
   case Tag::BOOL:
      return Type::BOOL;
   default:
      return Type::NOTYPE;
   }
}

Node::Node(TokenPtr token, Type type) :
   m_lexeme(token->get_lexeme()),
   m_type(type)
{}

std::string Node::to_string() const
{
   return m_lexeme;
}

Type Node::get_type() const
{
   return m_type;
}

}
