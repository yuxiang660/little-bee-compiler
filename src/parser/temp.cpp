#include "parser/temp.h"
#include "lexer/tag.h"

#include <memory>

namespace LBC
{

NodePtr NodeFactory::make_temp_node(Type type)
{
   return std::make_shared<TempNode>(type);
}

int TempNode::s_temp_id = 0;

TempNode::TempNode(Type type) :
   m_type(type),
   m_id(++s_temp_id)
{}

std::string TempNode::to_string() const
{
   return "t" + std::to_string(m_id);
}

Type TempNode::get_type() const
{
   return m_type;
}

}
