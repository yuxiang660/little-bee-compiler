#pragma once

#include "parser/op.h"
#include "parser/type.h"

#include <string>

namespace LBC
{

class RelNode: public OpNode
{
public:
   RelNode(NodePtr op, NodePtr lhs, NodePtr rhs): OpNode(op, lhs, rhs) {}
   Type get_type() const { return Type::BOOL; }
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
