#include "lexer.h"
#include "token.h"
#include "type.h"

#include <iostream>

namespace LBC
{

TokenPtr Lexer::scan()
{
   std::cout << "hello scan " << std::endl;
   return nullptr;
}

}
