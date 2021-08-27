#pragma once

#include "lexer/token.h"
#include <string>
#include <sstream>

namespace LBC
{

template<typename T>
static constexpr Tag get_num_tag()
{
   return std::is_same_v<T, float> ? Tag::REAL : Tag::INTEGER;
}

template<typename T>
static constexpr T string_to_val(std::string val)
{
   return std::is_same_v<T, float> ? std::stof(val) : std::stoi(val);
}

template<typename T>
class Num: public Token
{
public:
   explicit Num(const char* val):
      Token(val, get_num_tag<T>()),
      m_val(string_to_val<T>(val))
   {}

   T get_val() const { return m_val; }

private:
   const T m_val;
};

typedef Num<int> Integer;
typedef Num<float> Float;

}
