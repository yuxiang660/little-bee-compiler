#include "parser/temp.h"

#include <memory>

namespace LBC
{

NodePtr NodeFactory::make_temp_node()
{
   return std::make_shared<TempNode>();
}

int TempNode::s_temp_id = 0;

TempNode::TempNode() :
   m_id(++s_temp_id)
{}

std::string TempNode::to_string() const
{
   return "t" + std::to_string(m_id);
}

}
