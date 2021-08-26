#pragma once

#include "lexer/token.h"
#include "internal/node.h"

#include <memory>
#include <unordered_map>

namespace LBC
{

typedef std::unordered_map<TokenPtr, NodePtr> SymbolMap;

class Env : public std::enable_shared_from_this<Env>
{
public:
   explicit Env(std::shared_ptr<const Env> prev_env);
   void put(TokenPtr token, NodePtr symbol);
   NodePtr get(TokenPtr token) const;

private:
   std::shared_ptr<const Env> m_prev_env;
   SymbolMap m_table;
};

}
