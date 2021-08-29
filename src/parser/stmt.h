#pragma once

#include "parser/node.h"

#include <iostream>
#include <memory>

namespace LBC
{

class StmtInterface
{
public:
   virtual int prog_stmt(std::ostream& out) const = 0;
   virtual ~StmtInterface() = default;
};

typedef std::shared_ptr<StmtInterface> StmtPtr;

class Stmt: public StmtInterface
{
public:
   static int gen_unique_label();

public:
   Stmt(int label);
   int prog_stmt(std::ostream& out) const;

private:
   int m_label;
};

// class If: public StmtInterface
// {
// public:
//    explicit If(int stmt_label, NodePtr bool_expr);
//    int prog_stmt(std::ostream& out) const;

// private:
//    int m_stmt_label;
//    NodePtr m_bool_expr;
// };

}