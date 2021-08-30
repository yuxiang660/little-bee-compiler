#pragma once

#include "stmt/stmt.h"

namespace LBC
{

class If: public Stmt
{
public:
   If(int label, NodePtr expr);
   int prog_stmt(std::ostream& out) const;

private:
   NodePtr m_expr;
};

}
