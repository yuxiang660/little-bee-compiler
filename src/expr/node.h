#pragma once

#include "lexer/token.h"
#include "expr/type.h"

#include <iostream>
#include <memory>
#include <string>

namespace LBC
{

class NodeInterface
{
public:
   /**
    * @brief Gets output string of the node to generate three address code.
    * @return std::string, the string of the node.
    */
   virtual std::string to_string() const = 0;

   /**
    * @brief Gets the type of the node.
    * @return Type, the type of the node.
    */
   virtual Type get_type() const = 0;

   virtual ~NodeInterface() = default;
};

typedef std::shared_ptr<NodeInterface> NodePtr;

class Node: public NodeInterface
{
public:
   static NodePtr make_node(TokenPtr token);
   static Type get_tag_type(Tag t);

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
   /**
    * @brief Prints the three address code of the class.
    * @param out the output desitination
    * @return NodePtr, the result node after print, such as temp node.
    */
   virtual NodePtr prog_expr(std::ostream& out) const = 0;

   virtual ~GenInterface() = default;
};

}
