#pragma once

#include "lexer/token.h"
#include "lexer/tag.h"

namespace LBC
{

class Type: public Token
{
public:
   Type(const char* lexeme, Tag tag, int width): Token(lexeme, tag), m_width(width) {}
   int get_width() const { return m_width; }

private:
   const int m_width;
};

const Type INT_TYPE("int", Tag::INT, 4);
const Type FLOAT_TYPE("float", Tag::FLOAT, 8);
const Type CHAR_TYPE("char", Tag::CHAR, 1);
const Type BOOL_TYPE("bool", Tag::BOOL, 1);

}
