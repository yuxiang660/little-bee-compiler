#include "lexer/lexer.h"
#include "lexer/token.h"
#include "lexer/type.h"

#include <iostream>

namespace LBC
{

int Lexer::s_line = 1;

Lexer::Lexer()
{
   init_word_map();
}

void Lexer::init_word_map()
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
   std::cout << "hello scan " << std::endl;
   return m_words["else"];
}

}
