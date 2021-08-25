#pragma once

#include <cstring>
#include <memory>
#include <unordered_map>

namespace LBC
{

class TokenInterface;

typedef std::shared_ptr<TokenInterface> TokenPtr;

class LexerInterface
{
public:
   virtual TokenPtr scan() = 0;
   virtual ~LexerInterface() = default;
};

class Lexer: public LexerInterface
{
public:
   static int s_line;

public:
   Lexer() = default;
   TokenPtr scan();

public:
   Lexer(const Lexer&) = delete;
   Lexer& operator=(const Lexer&) = delete;

private:
   char m_peek;
   std::unordered_map<std::string, TokenPtr> m_keywords;
};

}
