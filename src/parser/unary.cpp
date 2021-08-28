#include "parser/unary.h"
#include "parser/temp.h"

#include <cassert>
#include <memory>

namespace LBC
{

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

UnaryGen::UnaryGen(Tag unary_op, NodePtr unary_val):
   m_op(unary_op),
   m_val(unary_val)
{}

NodePtr UnaryGen::program(std::ostream& out) const
{
   auto unary_node = std::make_shared<UnaryNode>(m_op, m_val);
   auto temp_node = std::make_shared<TempNode>(unary_node->get_type());
   out << temp_node->to_string() << " = " << unary_node->to_string() << std::endl;
   return temp_node;
}

}
