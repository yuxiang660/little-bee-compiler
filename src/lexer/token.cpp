#include "lexer/token.h"
#include "lexer/lexer.h"

namespace LBC
{

Token::Token(const char* lexeme, Tag t):
   m_lexeme(lexeme),
   m_tag(t)
{}

Tag Token::get_tag() const
{
   return m_tag;
}

std::string Token::get_lexeme() const
{
   return m_lexeme;
}

std::string Token::err_message() const
{
   std::string msg = "Syntax error near line " + std::to_string(Lexer::s_line) + " : " + m_lexeme;
   return msg;
}


}
