#include "lexer/lexer.h"
#include "lexer/num.h"
#include "lexer/token.h"
#include "lexer/type.h"
#include "internal/error.h"

#include <cctype>
#include <iostream>
#include <memory>
#include <sstream>

namespace LBC
{

int Lexer::s_line = 1;

Lexer::Lexer(std::istream& in):
   m_in(in),
   m_peek(' ')
{
   init_keywords();
}

void Lexer::readch()
{
   m_peek = m_in.get();
}

bool Lexer::readch(char c)
{
   readch();
   if (m_peek != c) return false;
   m_peek = ' ';
   return true;
}

void Lexer::init_keywords()
{
   auto insert_keyword = [&words = this->m_words](const char* lexeme, Tag tag) {
      words[lexeme] = std::make_shared<Token>(lexeme, tag);
   };
   insert_keyword("if", Tag::IF);
   insert_keyword("else", Tag::ELSE);
   insert_keyword("while", Tag::WHILE);
   insert_keyword("do", Tag::DO);
   insert_keyword("break", Tag::BREAK);
   insert_keyword("continue", Tag::CONTINUE);
   insert_keyword("true", Tag::TRUE);
   insert_keyword("false", Tag::FALSE);
   insert_keyword("&&", Tag::AND);
   insert_keyword("||", Tag::OR);
   insert_keyword("==", Tag::EQ);
   insert_keyword("!=", Tag::NE);
   insert_keyword("<=", Tag::LE);
   insert_keyword(">=", Tag::GE);
   insert_keyword("+", Tag::ADD);
   insert_keyword("-", Tag::SUB);
   insert_keyword("*", Tag::MUL);
   insert_keyword("/", Tag::DIV);
   insert_keyword("!", Tag::NOT);
   insert_keyword("=", Tag::ASSIGN);
   insert_keyword(">", Tag::GREAT);
   insert_keyword("<", Tag::LESS);
   insert_keyword("&", Tag::BITAND);
   insert_keyword("|", Tag::BITOR);
   insert_keyword("[", Tag::LINDEX);
   insert_keyword("]", Tag::RINDEX);
   insert_keyword("(", Tag::LBRACK);
   insert_keyword(")", Tag::RBRACK);
   insert_keyword("EOF", Tag::STOP);

   auto insert_type = [&words = this->m_words](const Type& type) {
      words[type.get_lexeme()] = std::make_shared<Type>(type.get_lexeme().c_str(), type.get_width());
   };
   insert_type(INT_TYPE);
   insert_type(FLOAT_TYPE);
   insert_type(CHAR_TYPE);
   insert_type(BOOL_TYPE);
}

TokenPtr Lexer::scan()
{
   for (; ; readch()) {
      if (m_peek == ' ' || m_peek == '\t') continue;
      else if (m_peek == '\n') s_line += 1;
      else
         break;
   }
   switch (m_peek)
   {
      case '&':
         return readch('&') ? m_words["&&"] : m_words["&"];
      case '|':
         return readch('|') ? m_words["||"] : m_words["|"];
      case '=':
         return readch('=') ? m_words["=="] : m_words["="];
      case '!':
         return readch('=') ? m_words["!="] : m_words["!"];
      case '<':
         return readch('=') ? m_words["<="] : m_words["<"];
      case '>':
         return readch('=') ? m_words[">="] : m_words[">"];
   }

   if (isdigit(m_peek) || m_peek == '.') {
      std::string number;
      do {
            number.push_back(m_peek);
            readch();
      } while (isdigit(m_peek));

      if (m_peek == '.') {
         do {
            number.push_back(m_peek);
            readch();
         } while (isdigit(m_peek));
      }

      if (m_words.find(number) != m_words.end()) return m_words[number];

      if (number.find('.') != std::string::npos) {
         m_words[number] = std::make_shared<Float>(number.c_str());
         return m_words[number];
      }
      else {
         m_words[number] = std::make_shared<Integer>(number.c_str());
         return m_words[number];
      }
   }

   if (isalpha(m_peek) || m_peek == '_') {
      std::string symbol;
      do {
         symbol.push_back(m_peek);
         readch();
      } while (isalpha(m_peek) || isdigit(m_peek) || m_peek == '_');

      if (m_words.find(symbol) != m_words.end()) {
         return m_words[symbol];
      } else {
         m_words[symbol] = std::make_shared<Token>(symbol.c_str(), Tag::SYMBOL);
         return m_words[symbol];
      }
   }

   if (m_words.find({m_peek}) != m_words.end()) {
      auto token = m_words[{m_peek}];
      m_peek = ' ';
      return token;
   }

   if (m_peek == EOF) return m_words["EOF"];

   std::ostringstream oss;
   oss << "Invalid character: " << m_peek << std::endl;
   throw Exception(ERR_LEXER_INVALID_TOKEN, oss.str().c_str());
   return nullptr;
}

}
