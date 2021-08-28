#include <parser/rel.h>
#include <parser/arith.h>
#include <parser/temp.h>

#include <memory>

namespace LBC
{

RelNode::RelNode(NodePtr op, NodePtr lhs, NodePtr rhs):
   m_op(op),
   m_lhs(lhs),
   m_rhs(rhs)
{}

std::string RelNode::to_string() const
{
   return m_lhs->to_string() + " " + m_op->to_string() + " " + m_rhs->to_string();
}

Type RelNode::get_type() const
{
   return Type::BOOL;
}


RelGen::RelGen(NodePtr op, NodePtr lhs, NodePtr rhs, std::ostream& out):
   NodeGen(out),
   m_op(op),
   m_lhs(lhs),
   m_rhs(rhs)
{}

NodePtr RelGen::program()
{
   NodePtr lhs = m_lhs;
   if (typeid(*m_lhs.get()) == typeid(ArithNode)) {
      lhs = std::make_shared<TempNode>(m_lhs->get_type());
      m_out << lhs->to_string() << " = " << m_lhs->to_string() << std::endl;
   }

   NodePtr rhs = m_rhs;
   if (typeid(*m_rhs.get()) == typeid(ArithNode)) {
      rhs = std::make_shared<TempNode>(m_rhs->get_type());
      m_out << rhs->to_string() << " = " << m_rhs->to_string() << std::endl;
   }

   return std::make_shared<RelNode>(m_op, lhs, rhs);
}

}
