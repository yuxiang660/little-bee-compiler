#pragma once

#include "lexer/token.h"
#include <string>
#include <sstream>

namespace LBC
{

template<typename T>
constexpr Tag get_num_tag()
{
   return std::is_same_v<T, float> ? Tag::REAL : Tag::INTEGER;
}

template<typename T>
std::string to_string(T val)
{
   std::stringstream ss;
   ss << val;
   return ss.str();
}

template<typename T>
class Num: public Token
{
public:
   explicit Num(T val):
      Token(to_string(val).c_str(), get_num_tag<T>()),
      m_val(val)
   {}

   T get_val() const { return m_val; }

private:
   const T m_val;
};

typedef Num<int> Integer;
typedef Num<float> Float;

}
