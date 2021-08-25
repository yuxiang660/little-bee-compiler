#include "token.h"

namespace LBC
{

Token::Token(const char* lexeme, Tag t):
   m_lexeme(lexeme),
   m_tag(t)
{}

std::string Token::toString() const
{
   return m_lexeme;
}

}