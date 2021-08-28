#pragma once

#include "parser/node.h"
#include "parser/type.h"

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

class OpGen: public GenInterface
{
public:
   OpGen(NodePtr op, NodePtr lhs, NodePtr rhs);
   NodePtr program(std::ostream& out) const;

protected:
   NodePtr m_op;
   NodePtr m_lhs;
   NodePtr m_rhs;
};

}
