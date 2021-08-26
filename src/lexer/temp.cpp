#include "temp.h"

namespace LBC
{

int Temp::count = 0;

Temp::Temp():
   Token(("t" + std::to_string(count++)).c_str(), Tag::TEMP)
{}

}
