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

class Node: public NodeInterface
{
public:
   explicit Node(TokenPtr token);
   std::string to_string() const;

private:
   TokenPtr m_token;
};

}
