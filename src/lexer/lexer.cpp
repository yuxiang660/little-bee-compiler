#include "lexer/lexer.h"
#include "lexer/token.h"
#include "lexer/type.h"

#include <iostream>

namespace LBC
{

TokenPtr Lexer::scan()
{
   std::cout << "hello scan " << std::endl;
   return nullptr;
}

}
