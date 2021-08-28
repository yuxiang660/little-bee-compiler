#include "parser/symbol.h"

#include <memory>

namespace LBC
{
const int no_level = -1;

SymbolNode::SymbolNode(const char* name, Type type) :
   m_name(name),
   m_type(type),
   m_env(no_level)
{}

std::string SymbolNode::to_string() const
{
   if (m_env == no_level) return m_name;
   return m_name + "(" + std::to_string(m_env) + ")";
}

Type SymbolNode::get_type() const
{
   return m_type;
}

void SymbolNode::set_env(int l)
{
   m_env = l;
}

}
