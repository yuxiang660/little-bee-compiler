#include "parser/unary.h"

#include <cassert>
#include <memory>

namespace LBC
{

NodePtr NodeFactory::make_unary_node(Tag unary_op, NodePtr unary_val)
{
   return std::make_shared<UnaryNode>(unary_op, unary_val);
}

UnaryNode::UnaryNode(Tag unary_op, NodePtr unary_val):
   m_op(unary_op),
   m_val(unary_val)
{}

std::string UnaryNode::to_string() const
{
   const std::string not_str = "not";
   const std::string minus_str = "minus";
   if (m_op == Tag::NOT) return not_str + " " + m_val->to_string();

   assert(m_op == Tag::MINUS);
   return minus_str + " " + m_val->to_string();
}

Type UnaryNode::get_type() const
{
   if (m_op == Tag::NOT) return Type::BOOL;

   assert(m_op == Tag::MINUS);
   return m_val->get_type();
}

UnaryGen::UnaryGen(Tag unary_op, NodePtr unary_val, std::ostream& out):
   NodeGen(out),
   m_op(unary_op),
   m_val(unary_val)
{}

NodePtr UnaryGen::program()
{
   auto unary_node = NodeFactory::make_unary_node(m_op, m_val);
   auto temp_node = NodeFactory::make_temp_node();
   m_out << temp_node->to_string() << " = " << unary_node->to_string() << std::endl;
   return temp_node;
}

}
