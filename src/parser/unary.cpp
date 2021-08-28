#include "parser/unary.h"

#include <cassert>
#include <memory>

namespace LBC
{

NodePtr NodeFactory::make_unary_node(Tag tag, NodePtr unary)
{
   return std::make_shared<UnaryNode>(tag, unary);
}

UnaryNode::UnaryNode(Tag tag, NodePtr unary):
   m_tag(tag),
   m_unary(unary)
{}

std::string UnaryNode::to_string() const
{
   const std::string not_str = "not";
   const std::string minus_str = "minus";
   if (m_tag == Tag::NOT) return not_str + " " + m_unary->to_string();

   assert(m_tag == Tag::MINUS);
   return minus_str + " " + m_unary->to_string();
}

Type UnaryNode::get_type() const
{
   if (m_tag == Tag::NOT) return Type::BOOL;

   assert(m_tag == Tag::MINUS);
   return m_unary->get_type();
}

UnaryGen::UnaryGen(Tag tag, NodePtr unary, std::ostream& out):
   NodeGen(out),
   m_tag(tag),
   m_unary(unary)
{}

NodePtr UnaryGen::program()
{
   return NodeFactory::make_unary_node(m_tag, gen_unary_code(m_unary));
}

NodePtr UnaryGen::gen_unary_code(NodePtr node) {
   if (typeid(*node.get()) == typeid(UnaryNode)) {
      auto temp_node = NodeFactory::make_temp_node();
      m_out << temp_node->to_string() << " = " << node->to_string() << std::endl;
      return temp_node;
   }

   return node;
}

}
