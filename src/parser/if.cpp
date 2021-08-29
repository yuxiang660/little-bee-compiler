#include "parser/if.h"

namespace LBC
{

If::If(int label, NodePtr expr):
   Stmt(label),
   m_expr(expr)
{}

int If::prog_stmt(std::ostream& out) const
{
   int jump_label = Stmt::prog_stmt(out);
   out << "\t" << "if not " << m_expr->to_string() << " goto L" << jump_label << std::endl;
   return jump_label;
}

}
