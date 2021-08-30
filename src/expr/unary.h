#pragma once

#include "expr/node.h"
#include "expr/type.h"

#include <string>

namespace LBC
{

class UnaryNode: public NodeInterface
{
public:
   UnaryNode(Tag unary_op, NodePtr unary_val);
   std::string to_string() const;
   Type get_type() const;

private:
   Tag m_op;
   NodePtr m_val;
};

class UnaryGen: public GenInterface
{
public:
   UnaryGen(Tag unary_op, NodePtr unary_val);
   NodePtr prog_expr(std::ostream& out) const;

private:
   Tag m_op;
   NodePtr m_val;
};

}
