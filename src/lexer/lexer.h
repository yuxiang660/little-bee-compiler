#pragma once

#include "lexer/token.h"

#include <memory>
#include <string>
#include <unordered_map>

namespace LBC
{

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
   Lexer();
   TokenPtr scan();

public:
   Lexer(const Lexer&) = delete;
   Lexer& operator=(const Lexer&) = delete;

private:
   void init_word_map();

private:
   char m_peek;
   std::unordered_map<std::string, TokenPtr> m_words;
};

}
