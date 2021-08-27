#include "parser/arith.h"

#include <memory>


namespace LBC
{

NodePtr NodeFactory::make_arith_node(NodePtr op, NodePtr lhs, NodePtr rhs)
{
   return std::make_shared<ArithNode>(op, lhs, rhs);
}

ArithNode::ArithNode(NodePtr op, NodePtr lhs, NodePtr rhs):
   m_op(op),
   m_lhs(lhs),
   m_rhs(rhs)
{}

std::string ArithNode::to_string() const
{
   return m_lhs->to_string() + " " + m_op->to_string() + " " + m_rhs->to_string();
}

ArithGen::ArithGen(NodePtr op, NodePtr lhs, NodePtr rhs, std::ostream& out):
   NodeGen(out),
   m_op(op),
   m_lhs(lhs),
   m_rhs(rhs)
{}

NodePtr ArithGen::program()
{
   return NodeFactory::make_arith_node(m_op, gen_arith_code(m_lhs), gen_arith_code(m_rhs));
}

NodePtr ArithGen::gen_arith_code(NodePtr node) {
   if (typeid(*node.get()) == typeid(ArithNode)) {
      auto temp_node = NodeFactory::make_temp_node();
      m_out << temp_node->to_string() << " = " << node->to_string() << std::endl;
      return temp_node;
   }

   return node;
}

}
