#include "parser/node.h"

namespace LBC
{

NodePtr NodeFactory::make_node(TokenPtr token)
{
   return std::make_shared<Node>(token);
}

Node::Node(TokenPtr token) :
   m_lexeme(token->get_lexeme()),
   m_type(token->get_tag())
{}

std::string Node::to_string() const
{
   return m_lexeme;
}

Tag Node::get_type() const
{
   return m_type;
}

NodeGen::NodeGen(std::ostream& out):
   m_out(out)
{}

}
