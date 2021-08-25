#include "lexer/lexer.h"
#include <iostream>

int main(int argc, char const *argv[])
{
   std::cout << "main" << std::endl;
   auto l = LBC::Lexer();
   l.scan();
   return 0;
}

