#include "parser/stmt.h"

namespace LBC
{

int Stmt::gen_unique_label()
{
   static int lable_seed = 0;
   return ++lable_seed;
}

Stmt::Stmt(int label):
   m_label(label)
{}

int Stmt::prog_stmt(std::ostream& out) const
{
   out << "L" << m_label << ":";
   return gen_unique_label();
}

// If::If(int stmt_label, NodePtr bool_expr):
//    m_stmt_label(stmt_label),
//    m_bool_expr(bool_expr)
// {}

}
