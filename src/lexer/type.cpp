#include "type.h"
#include "tag.h"

namespace LBC
{

Type::Type(const char* lexeme, int width):
   Token(lexeme, Tag::BASIC),
   m_width(width)
{}

}

