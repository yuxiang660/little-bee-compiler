#pragma once

#include "parser/node.h"
#include "lexer/lexer.h"
#include "internal/error.h"
#include "env/env.h"

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
    *    "program" is parser top level function.
    *    It handles exception from block() and begin/end label.
    *    Returns error code, 0: success, other: failure.
    * Grammar:
    *    program -> block
    */
   int program();

   /*
    * Desc:
    *    "block" starts with "{" token, ends with "}" token.
    *    It handles "{", "}".
    * Grammar:
    *    block -> { decls stmts }
    */
   void block(bool is_outermost = false);

   /*
    * Desc:
    *    "decls" is declaration statements.
    *    It handles "type id;".
    * Grammar:
    *    decls -> decl decls
    *           | ε
    *     decl -> type id id_rest ;
    *  id_rest -> , id id_rest
    *           | ε
    */
   void decls();

   /*
    * Desc:
    *    "stmts" parses all other statements in one block after declaration.
    *    It handles different statements, such as if/while/block statement.
    * Grammar:
    *    stmts -> stmt stmts
    *           | ε
    *     stmt -> 
    *           | if (boolean) stmt
    *           | if (boolean) stmt else stmt
    *           | while (boolean) stmts
    *           | do stmts while (boolean);
    *           | break;
    *           | continue;
    *           | block
    *           | assign
    */
   void stmts();

   /*
    * Desc:
    *    "assign" is assignment statement.
    *    It handles "=".
    * Grammar:
    *    assign -> symbol = boolean ;
    */
   void assign();

   /*
    * Desc:
    *    "boolean" connects two join(&&) expressions with OR operator "&||".
    *    It handles "||".
    * Grammar:
    *    boolean -> join rest
    *       rest -> || join rest
    *             | ε
    */
   NodePtr boolean();

   /*
    * Desc:
    *    "join" connects two equalities with AND operator "&&".
    *    It handles "&&".
    * Grammar:
    *    join -> equality rest
    *    rest -> && equality rest
    *          | ε
    */
   NodePtr join();

   /*
    * Desc:
    *    "equality" is compare operation between two exrpression
    *    It handles "==, !=".
    * Grammar:
    *    equality -> rel == rel | rel != rel | rel
    */
   NodePtr equality();

   /*
    * Desc:
    *    "rel" is relative operation between two exrpression, which can be deduced to relative
    *    operation between two numbers.
    *    It handles "<, <=, >, >=".
    * Grammar:
    *    rel -> expr <  expr
    *         | expr <= expr
    *         | expr >  expr
    *         | expr >= expr
    *         | expr
    */
   NodePtr rel();

   /*
    * Desc:
    *    "expr" is the arithmetic expression which can be deduced to a number.
    *    It handles "+, -".
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
    *    It handles "*, /".
    * Grammar:
    *    term -> unary rest
    *    rest -> * unary rest
    *          | / unary rest
    *          | ε
    */
   NodePtr term();

   /*
    * Desc:
    *    "unary" is an unary expression.
    *    It handles "-, !".
    * Grammar:
    *    unary -> !unary | -unary | factor
    */
   NodePtr unary();

   /*
    * Desc:
    *    "factor" is a number, or an expression with "()".
    *    It handles "numbers, ()"
    * Grammar:
    *    factor -> (expr) | digital
    */
   NodePtr factor();

private:
   void move_ahead(int count, ...);

private:
   Lexer& m_lex;
   std::ostream& m_out;
   EnvPtr m_cur_env;
   TokenPtr m_look;
};

}
