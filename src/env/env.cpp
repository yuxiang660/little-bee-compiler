#include "env/env.h"

namespace LBC
{

Env::Env(std::shared_ptr<const Env> prev_env):
   m_prev_env(prev_env)
{}

void Env::put(TokenPtr token, NodePtr symbol)
{
   m_table[token] = symbol;
}

NodePtr Env::get(TokenPtr token) const
{
   for (auto e = shared_from_this(); e.get() != nullptr; e = m_prev_env) {
      auto found = e->m_table.find(token);
      if (found != e->m_table.end()) return found->second;
   }
   return nullptr;
}

}
