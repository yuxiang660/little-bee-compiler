#pragma once

#include "lexer/tag.h"

#include <string>
#include <vector>

namespace LBC
{

class TokenInterface
{
public:
   virtual std::string toString() const = 0;
   virtual ~TokenInterface() = default;
};

class Token: public TokenInterface
{
public:
   explicit Token(const char* lexeme, Tag t = Tag::OTHER);
   std::string toString() const;
   Tag get_tag() const;
   std::string get_lexeme() const;

private:
   const std::string m_lexeme;
   const Tag m_tag;
};

}
