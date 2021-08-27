#include "internal/node.h"

namespace LBC
{

Node::Node(TokenPtr token) :
   m_gen_code(token->get_lexeme())
{}

Node::Node(const char* code) :
   m_gen_code(code)
{}

NodePtr NodeFactory::make_node(TokenPtr token)
{
   return std::make_shared<Node>(token->get_lexeme().c_str());
}

NodePtr NodeFactory::make_node(const char* code)
{
   return std::make_shared<Node>(code);
}

NodePtr NodeFactory::make_temp_node()
{
   static int temp_id = 0;
   std::string temp_name = "t" + std::to_string(temp_id++);
   return std::make_shared<Node>(temp_name.c_str());
}

std::string Node::to_string() const
{
   return m_gen_code;
}

}
