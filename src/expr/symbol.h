#pragma once

#include "expr/node.h"
#include "expr/type.h"

#include <string>

namespace LBC
{

class SymbolNode: public NodeInterface
{
public:
   explicit SymbolNode(const char* name, Type type);
   void set_env(int l);
   std::string to_string() const;
   Type get_type() const;

private:
   const std::string m_name;
   Type m_type;
   int m_env;
};

}
