#pragma once

#include "expr/op.h"
#include "expr/type.h"

#include <string>

namespace LBC
{

class RelNode: public OpNode
{
public:
   RelNode(NodePtr op, NodePtr lhs, NodePtr rhs): OpNode(op, lhs, rhs) {}
   Type get_type() const;
};


class RelGen: public GenInterface
{
public:
   RelGen(NodePtr op, NodePtr lhs, NodePtr rhs);
   NodePtr prog_expr(std::ostream& out) const;

private:
   NodePtr m_op;
   NodePtr m_lhs;
   NodePtr m_rhs;
};

}
