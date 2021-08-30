#include <expr/rel.h>
#include <expr/arith.h>
#include <expr/temp.h>

#include <cassert>
#include <memory>

namespace LBC
{

Type RelNode::get_type() const {
   assert(m_lhs->get_type() == m_rhs->get_type());
   return Type::BOOL;
}

RelGen::RelGen(NodePtr op, NodePtr lhs, NodePtr rhs):
   m_op(op),
   m_lhs(lhs),
   m_rhs(rhs)
{}

NodePtr RelGen::prog_expr(std::ostream& out) const
{
   NodePtr lhs = m_lhs;
   if (typeid(*m_lhs.get()) == typeid(ArithNode) || typeid(*m_lhs.get()) == typeid(RelNode)) {
      lhs = std::make_shared<TempNode>(m_lhs->get_type());
      out << "\t" << lhs->to_string() << " = " << m_lhs->to_string() << std::endl;
   }

   NodePtr rhs = m_rhs;
   if (typeid(*m_rhs.get()) == typeid(ArithNode) || typeid(*m_rhs.get()) == typeid(RelNode)) {
      rhs = std::make_shared<TempNode>(m_rhs->get_type());
      out << "\t" << rhs->to_string() << " = " << m_rhs->to_string() << std::endl;
   }

   return std::make_shared<RelNode>(m_op, lhs, rhs);
}

}
