#pragma once

#include "lexer/token.h"

#include <memory>
#include <iostream>
#include <string>

namespace LBC
{

class NodeInterface
{
public:
   virtual std::string to_string() const = 0;
   virtual ~NodeInterface() = default;
};

typedef std::shared_ptr<NodeInterface> NodePtr;

class NodeFactory
{
public:
   static NodePtr make_node(TokenPtr token);
   static NodePtr make_arith_node(const char* code);
   static NodePtr make_temp_node();
};

class Node: public NodeInterface
{
public:
   explicit Node(TokenPtr token);
   std::string to_string() const;

private:
   std::string m_gen_code;
};

class ArithNode: public NodeInterface
{
public:
   explicit ArithNode(const char* arith);
   std::string to_string() const;

private:
   std::string m_gen_code;
};

class TempNode: public NodeInterface
{
public:
   static int s_temp_id;

public:
   TempNode();
   std::string to_string() const;

private:
   int m_id;
};

}
