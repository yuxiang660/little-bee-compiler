#pragma once

namespace LBC
{

enum class Tag
{
   AND,     // &&
   BASIC,   // int, float, char, bool
   BREAK,   // break
   DO,      // do
   ELSE,    // else
   EQ,      // ==
   FALSE,   // false
   GE,      // >=
   SYMBOL,  // symbol, such as variable name
   IF,      // if
   INDEX,   // []
   LE,      // <=
   MINUS,   // -
   NE,      // !=
   INTEGER, // integer number
   OR,      // ||
   REAL,    // decimals
   STOP,    // stop flag, such as EOF
   TEMP,    // t, temporary var for three-address instruction
   TRUE,    // true
   WHILE,   // while
   CONTINUE,// continue
   // Single char
   ADD,     // +
   SUB,     // -
   MUL,     // *
   DIV,     // /
   NOT,     // !
   ASSIGN,  // =
   GREAT,   // >
   LESS,    // <
   BITAND,  // &
   BITOR,   // |
   LINDEX,  // [
   RINDEX,  // ]
   LBRACK,  // (
   RBRACK   // )
};

}
