#pragma once

#include "lexer/token.h"
#include "lexer/tag.h"

#include <memory>
#include <iostream>
#include <string>

namespace LBC
{

class NodeInterface
{
public:
   virtual std::string to_string() const = 0;
   virtual Tag get_type() const = 0;
   virtual ~NodeInterface() = default;
};

typedef std::shared_ptr<NodeInterface> NodePtr;

class NodeFactory
{
public:
   static NodePtr make_node(TokenPtr token);
   static NodePtr make_temp_node();
   static NodePtr make_arith_node(NodePtr op, NodePtr lhs, NodePtr rhs);
   static NodePtr make_unary_node(Tag tag, NodePtr unary);
};

class Node: public NodeInterface
{
public:
   explicit Node(TokenPtr token);
   std::string to_string() const;
   Tag get_type() const;

private:
   std::string m_lexeme;
   Tag m_type;
};

class GenInterface
{
public:
   virtual ~GenInterface() = default;
};

class NodeGen: public GenInterface
{
public:
   explicit NodeGen(std::ostream& out);

protected:
   std::ostream& m_out;
};


}
