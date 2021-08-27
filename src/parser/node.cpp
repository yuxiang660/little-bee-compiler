#include "parser/node.h"

namespace LBC
{

NodePtr NodeFactory::make_node(TokenPtr token)
{
   return std::make_shared<Node>(token);
}

NodePtr NodeFactory::make_arith_node(const char* code)
{
   return std::make_shared<ArithNode>(code);
}

NodePtr NodeFactory::make_temp_node()
{
   return std::make_shared<TempNode>();
}

Node::Node(TokenPtr token) :
   m_gen_code(token->get_lexeme())
{}

std::string Node::to_string() const
{
   return m_gen_code;
}

ArithNode::ArithNode(const char* code) :
   m_gen_code(code)
{}

std::string ArithNode::to_string() const
{
   return m_gen_code;
}

int TempNode::s_temp_id = 0;

TempNode::TempNode() :
   m_id(s_temp_id)
{}

std::string TempNode::to_string() const
{
   return "t" + std::to_string(m_id);
}

}
