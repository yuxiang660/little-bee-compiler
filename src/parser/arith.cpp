#include "parser/arith.h"
#include "parser/temp.h"

#include <cassert>
#include <memory>


namespace LBC
{

ArithNode::ArithNode(NodePtr op, NodePtr lhs, NodePtr rhs):
   m_op(op),
   m_lhs(lhs),
   m_rhs(rhs)
{}

std::string ArithNode::to_string() const
{
   return m_lhs->to_string() + " " + m_op->to_string() + " " + m_rhs->to_string();
}

Type ArithNode::get_type() const
{
   assert(m_lhs->get_type() == m_rhs->get_type());
   return m_lhs->get_type();
}

ArithGen::ArithGen(NodePtr op, NodePtr lhs, NodePtr rhs):
   m_op(op),
   m_lhs(lhs),
   m_rhs(rhs)
{}

NodePtr ArithGen::program(std::ostream& out) const
{
   return std::make_shared<ArithNode>(m_op, gen_arith_code(m_lhs, out), gen_arith_code(m_rhs, out));
}

NodePtr ArithGen::gen_arith_code(NodePtr node, std::ostream& out) const {
   if (typeid(*node.get()) == typeid(ArithNode)) {
      auto temp_node = std::make_shared<TempNode>(node->get_type());
      out << temp_node->to_string() << " = " << node->to_string() << std::endl;
      return temp_node;
   }

   return node;
}

}
