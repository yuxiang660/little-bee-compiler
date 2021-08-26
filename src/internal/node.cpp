#include "internal/node.h"

namespace LBC
{

Node::Node(TokenPtr token) :
   m_token(token)
{}

std::string Node::to_string() const
{
   return m_token->get_lexeme();
}

}
