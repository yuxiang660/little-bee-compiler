#include "parser/node.h"

namespace LBC
{

NodePtr NodeFactory::make_node(TokenPtr token)
{
   return std::make_shared<Node>(token);
}

Node::Node(TokenPtr token) :
   m_lexeme(token->get_lexeme())
{}

std::string Node::to_string() const
{
   return m_lexeme;
}

NodeGen::NodeGen(std::ostream& out):
   m_out(out)
{}

}
