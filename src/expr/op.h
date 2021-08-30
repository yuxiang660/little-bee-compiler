#pragma once

#include "expr/node.h"
#include "expr/type.h"

#include <string>

namespace LBC
{

class OpNode: public NodeInterface
{
public:
   OpNode(NodePtr op, NodePtr lhs, NodePtr rhs);
   std::string to_string() const;
   Type get_type() const;

protected:
   NodePtr m_op;
   NodePtr m_lhs;
   NodePtr m_rhs;
};

}
