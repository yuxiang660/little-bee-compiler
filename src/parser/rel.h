#pragma once

#include "parser/node.h"
#include "parser/type.h"

#include <string>

namespace LBC
{

class RelNode: public NodeInterface
{
public:
   RelNode(NodePtr op, NodePtr lhs, NodePtr rhs);
   std::string to_string() const;
   Type get_type() const;

private:
   NodePtr m_op;
   NodePtr m_lhs;
   NodePtr m_rhs;
};


class RelGen: public GenInterface
{
public:
   RelGen(NodePtr op, NodePtr lhs, NodePtr rhs);
   NodePtr program(std::ostream& out) const;

private:
   NodePtr m_op;
   NodePtr m_lhs;
   NodePtr m_rhs;
};

}
