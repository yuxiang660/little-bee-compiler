#include "lexer/type.h"
#include "lexer/tag.h"

namespace LBC
{

Type::Type(const char* lexeme, int width):
   Token(lexeme, Tag::BASIC),
   m_width(width)
{}

}

