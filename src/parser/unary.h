#pragma once

#include "parser/node.h"
#include "parser/type.h"

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

class UnaryGen: public NodeGen
{
public:
   UnaryGen(Tag unary_op, NodePtr unary_val, std::ostream& out);
   NodePtr program();

private:
   Tag m_op;
   NodePtr m_val;
};

}
