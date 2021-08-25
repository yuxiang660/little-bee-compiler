#pragma once

#include "lexer/token.h"

namespace LBC
{

template<typename T>
constexpr Tag get_num_tag()
{
   return std::is_same_v<T, float> ? Tag::REAL : Tag::INTEGER;
}

template<typename T>
class Num: public Token
{
public:
   explicit Num(T val):
      Token(std::to_string(val).c_str(), get_num_tag<T>()),
      m_val(val)
   {}

private:
   const T m_val;
};

typedef Num<int> Integer;
typedef Num<float> Float;

}
