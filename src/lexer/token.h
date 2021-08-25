#pragma once

#include "tag.h"

#include <string>

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
   Token(const char* lexeme, Tag t = Tag::OTHER);
   std::string toString() const;

private:
   const std::string m_lexeme;
   const Tag m_tag;
};

const Token AND_TOKEN("&&", Tag::AND);
const Token OR_TOKEN("||", Tag::OR);
const Token EQ_TOKEN("==", Tag::EQ);
const Token NE_TOKEN("!=", Tag::NE);
const Token LE_TOKEN("<=", Tag::LE);
const Token GE_TOKEN(">=", Tag::GE);
const Token IF_TOKEN("if", Tag::IF);
const Token ELSE_TOKEN("else", Tag::ELSE);
const Token WHILE_TOKEN("while", Tag::WHILE);
const Token DO_TOKEN("do", Tag::DO);
const Token BREAK_TOKEN("break", Tag::BREAK);
const Token CONTINUE_TOKEN("continue", Tag::CONTINUE);
const Token TRUE_TOKEN("true", Tag::TRUE);
const Token FALSE_TOKEN("false", Tag::FALSE);

const Token MINUS_TOKEN("minus", Tag::MINUS);
const Token TEMP_TOKEN("t", Tag::TEMP);

}