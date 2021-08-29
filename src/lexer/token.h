#pragma once

#include "lexer/tag.h"

#include <memory>
#include <string>
#include <vector>

namespace LBC
{

class TokenInterface
{
public:
   virtual Tag get_tag() const = 0;
   virtual std::string get_lexeme() const = 0;
   virtual std::string err_message() const = 0;
   virtual ~TokenInterface() = default;
};

typedef std::shared_ptr<TokenInterface> TokenPtr;

class Token: public TokenInterface
{
public:
   Token(const char* lexeme, Tag t);
   Tag get_tag() const;
   std::string get_lexeme() const;
   std::string err_message() const;

private:
   const std::string m_lexeme;
   const Tag m_tag;
};

}
