#include "parser/arith.h"
#include "parser/temp.h"

#include <cassert>
#include <memory>


namespace LBC
{

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
      out << "\t" << temp_node->to_string() << " = " << node->to_string() << std::endl;
      return temp_node;
   }

   return node;
}

}
