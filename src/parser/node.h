#pragma once

#include "lexer/token.h"
#include "parser/type.h"

#include <memory>
#include <iostream>
#include <string>

namespace LBC
{

class NodeInterface
{
public:
   virtual std::string to_string() const = 0;
   virtual Type get_type() const = 0;
   virtual ~NodeInterface() = default;
};

typedef std::shared_ptr<NodeInterface> NodePtr;

class NodeFactory
{
public:
   static NodePtr make_node(TokenPtr token, Type type = Type::NOTYPE);
   static NodePtr make_temp_node(Type type);
   static NodePtr make_arith_node(NodePtr op, NodePtr lhs, NodePtr rhs);
   static NodePtr make_unary_node(Tag unary_op, NodePtr unary_val);
};

class Node: public NodeInterface
{
public:
   explicit Node(TokenPtr token, Type type);
   std::string to_string() const;
   Type get_type() const;

private:
   std::string m_lexeme;
   Type m_type;
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
