#pragma once

#include "lexer/token.h"
#include "parser/node.h"

#include <memory>
#include <unordered_map>

namespace LBC
{

typedef std::unordered_map<TokenPtr, NodePtr> SymbolMap;

class Env : public std::enable_shared_from_this<Env>
{
public:
   static int s_level;

public:
   explicit Env(std::shared_ptr<Env> prev_env);
   void put(TokenPtr token, NodePtr symbol);
   bool is_redefine(TokenPtr token) const;
   NodePtr get(TokenPtr token) const;

private:
   int m_level;
   std::shared_ptr<Env> m_prev_env;
   SymbolMap m_table;
};

typedef std::shared_ptr<Env> EnvPtr;

}
