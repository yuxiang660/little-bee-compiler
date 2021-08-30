#pragma once

#include "expr/node.h"

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
   static int s_lable_seed;
   static int gen_unique_label();

public:
   explicit Stmt(int label);
   int prog_stmt(std::ostream& out) const;

private:
   int m_label;
};

}
