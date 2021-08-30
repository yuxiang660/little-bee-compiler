#include "expr/op.h"

#include <cassert>
#include <memory>

namespace LBC
{

OpNode::OpNode(NodePtr op, NodePtr lhs, NodePtr rhs):
   m_op(op),
   m_lhs(lhs),
   m_rhs(rhs)
{}

std::string OpNode::to_string() const
{
   return m_lhs->to_string() + " " + m_op->to_string() + " " + m_rhs->to_string();
}

Type OpNode::get_type() const
{
   assert(m_lhs->get_type() == m_rhs->get_type());
   return m_lhs->get_type();
}

}
