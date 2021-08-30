#include "stmt/assign.h"

namespace LBC
{

Assign::Assign(int label, NodePtr symbol, NodePtr expr):
   Stmt(label),
   m_symbol(symbol),
   m_expr(expr)
{}

int Assign::prog_stmt(std::ostream& out) const
{
   int next_label = Stmt::prog_stmt(out);
   out << "\t" << m_symbol->to_string() << " = " << m_expr->to_string() << std::endl;
   return next_label;
}

}
