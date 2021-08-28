#pragma once

#include "parser/node.h"
#include "parser/type.h"

#include <string>

namespace LBC
{

class ArithNode: public NodeInterface
{
public:
   ArithNode(NodePtr op, NodePtr lhs, NodePtr rhs);
   std::string to_string() const;
   Type get_type() const;

private:
   NodePtr m_op;
   NodePtr m_lhs;
   NodePtr m_rhs;
};

class ArithGen: public GenInterface
{
public:
   ArithGen(NodePtr op, NodePtr lhs, NodePtr rhs);
   NodePtr program(std::ostream& out) const;

private:
   NodePtr gen_arith_code(NodePtr node, std::ostream& out) const;

private:
   NodePtr m_op;
   NodePtr m_lhs;
   NodePtr m_rhs;
};

}
