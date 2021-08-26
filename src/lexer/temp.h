#pragma once

#include "lexer/token.h"
#include "lexer/tag.h"

#include <string>

namespace LBC
{

class Temp: public Token
{
public:
   static int count;

public:
   Temp();
};

}
