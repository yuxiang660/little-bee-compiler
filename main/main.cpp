#include "lexer/lexer.h"
#include "parser/parser.h"
#include <iostream>

int main(int argc, char const *argv[])
{
   std::cout << "main" << std::endl;
   auto l = LBC::Lexer();
   auto parser = LBC::Parser(l);
   return parser.program();
}

