#pragma once

#include "parser/node.h"
#include "parser/type.h"

#include <string>

namespace LBC
{

class TempNode: public NodeInterface
{
public:
   static int s_temp_id;

public:
   TempNode();
   std::string to_string() const;
   Type get_type() const;

private:
   int m_id;
};

}
