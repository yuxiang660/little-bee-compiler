#include "stmt/stmt.h"

namespace LBC
{

int Stmt::s_lable_seed = 0;

int Stmt::gen_unique_label()
{
   return ++s_lable_seed;
}

Stmt::Stmt(int label):
   m_label(label)
{}

int Stmt::prog_stmt(std::ostream& out) const
{
   out << "L" << m_label << ":";
   return gen_unique_label();
}

}
