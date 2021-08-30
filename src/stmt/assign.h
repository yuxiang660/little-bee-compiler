#pragma once

#include "stmt/stmt.h"
#include "expr/node.h"

namespace LBC
{

class Assign: public Stmt
{
public:
   Assign(int label, NodePtr symbol, NodePtr expr);
   int prog_stmt(std::ostream& out) const;

private:
   NodePtr m_symbol;
   NodePtr m_expr;
};

}
