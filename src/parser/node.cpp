#include "parser/node.h"

namespace LBC
{

NodePtr Node::make_node(TokenPtr token, Type type)
{
   return std::make_shared<Node>(token, type);
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
