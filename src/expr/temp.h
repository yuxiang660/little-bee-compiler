#pragma once

#include "expr/node.h"
#include "expr/type.h"

#include <string>

namespace LBC
{

class TempNode: public NodeInterface
{
public:
   static int s_temp_id;

public:
   explicit TempNode(Type type);
   std::string to_string() const;
   Type get_type() const;

private:
   Type m_type;
   int m_id;
};

}
