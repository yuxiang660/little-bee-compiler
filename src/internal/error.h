#pragma once

#include <string>
#include <sstream>
#include <exception>

namespace LBC
{

struct Error
{
   int code;
   std::string des;
};

class Exception : public std::exception
{
public:
   explicit Exception(Error err, const char* msg = "") : m_err(err), m_msg(msg) {}

   const char* what() const noexcept
   {
      std::stringstream ss;
      ss << "LBC::ERROR(" << m_err.code << "): " << m_err.des << ". " << m_msg;
      return ss.str().c_str();
   }

   int code() const noexcept
   {
      return m_err.code;
   }

private:
   Error m_err;
   std::string m_msg;
};

const Error ERR_IVALID_TOKEN = {-1, "Fails to parse the token"};

}