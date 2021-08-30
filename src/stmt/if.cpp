#include "stmt/if.h"
#include "expr/arith.h"
#include "expr/rel.h"
#include "expr/temp.h"

#include <memory>

namespace LBC
{

If::If(int label, NodePtr expr):
   Stmt(label),
   m_expr(expr)
{}

int If::prog_stmt(std::ostream& out) const
{
   NodePtr expr = m_expr;
   if (typeid(*m_expr.get()) == typeid(ArithNode) || typeid(*m_expr.get()) == typeid(RelNode)) {
      expr = std::make_shared<TempNode>(m_expr->get_type());
      out << "\t" << expr->to_string() << " = " << m_expr->to_string() << std::endl;
   }

   int jump_label = Stmt::prog_stmt(out);
   out << "\t" << "if not " << expr->to_string() << " goto L" << jump_label << std::endl;
   return jump_label;
}

}
