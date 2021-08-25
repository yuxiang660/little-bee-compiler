#pragma once

#include "lexer/token.h"
#include "lexer/tag.h"

namespace LBC
{

class Type: public Token
{
public:
   Type(const char* lexeme, int width): Token(lexeme, Tag::BASIC), m_width(width) {}
   int get_width() const { return m_width; }

private:
   const int m_width;
};

const Type INT_TYPE("int", 4);
const Type FLOAT_TYPE("float", 8);
const Type CHAR_TYPE("char", 1);
const Type BOOL_TYPE("bool", 1);

}
