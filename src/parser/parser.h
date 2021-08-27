#pragma once

#include "parser/node.h"
#include "lexer/lexer.h"
#include "internal/error.h"

#include <cstdarg>
#include <iostream>

namespace LBC
{

class Parser
{
public:
   explicit Parser(Lexer& l, std::ostream& out = std::cout);

public:
   NodePtr expr();
   NodePtr term();
   NodePtr factor();

private:
   void match(int count, ...);

private:
   Lexer& m_lex;
   std::ostream& m_out;
   TokenPtr m_look;
};

}
