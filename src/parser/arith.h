#pragma once

#include "parser/node.h"

#include <string>

namespace LBC
{

class ArithNode: public NodeInterface
{
public:
   ArithNode(NodePtr op, NodePtr lhs, NodePtr rhs);
   std::string to_string() const;

private:
   NodePtr m_op;
   NodePtr m_lhs;
   NodePtr m_rhs;
};

class ArithGen: public NodeGen
{
public:
   ArithGen(NodePtr op, NodePtr lhs, NodePtr rhs, std::ostream& out);
   NodePtr program();

private:
   NodePtr gen_arith_code(NodePtr node);

private:
   NodePtr m_op;
   NodePtr m_lhs;
   NodePtr m_rhs;
};

}
