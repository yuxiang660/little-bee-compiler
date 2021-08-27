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
   /*
    * Desc:
    *    "expr" is the arithmetic expression which can be deduced to a number.
    *    It supports "+, -, *, / , ()".
    * Grammar:
    *    expr -> term rest
    *    rest -> + term rest
    *          | - term rest
    *          | ε
    */
   NodePtr expr();

   /*
    * Desc:
    *    "term" is the MUL and DIV expression which can be deduced to a number.
    *    It supports "*, / , ()".
    * Grammar:
    *    term -> unary rest
    *    rest -> * unary rest
    *          | / unary rest
    *          | ε
    */
   NodePtr term();

   /*
    * Desc:
    *    "unary" is an unary expression. It supports "-, !, ()".
    * Grammar:
    *    unary -> !unary | -unary | factor
    */
   NodePtr unary();

   /*
    * Desc:
    *    "factor" is a number, or an expression with "()".
    * Grammar:
    *    factor -> (expr) | digital
    */
   NodePtr factor();

private:
   void match(int count, ...);

private:
   Lexer& m_lex;
   std::ostream& m_out;
   TokenPtr m_look;
};

}
