#pragma once

#include "parser/node.h"
#include "parser/type.h"

#include <string>

namespace LBC
{

class UnaryNode: public NodeInterface
{
public:
   UnaryNode(Tag tag, NodePtr unary);
   std::string to_string() const;
   Type get_type() const;

private:
   Tag m_tag;
   NodePtr m_unary;
};

class UnaryGen: public NodeGen
{
public:
   UnaryGen(Tag tag, NodePtr unary, std::ostream& out);
   NodePtr program();

private:
   NodePtr gen_unary_code(NodePtr node);

private:
   Tag m_tag;
   NodePtr m_unary;
};

}
