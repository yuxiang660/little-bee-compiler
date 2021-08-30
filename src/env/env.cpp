#include "env/env.h"
#include "expr/symbol.h"

#include <cassert>
#include <memory>

namespace LBC
{

int Env::s_id = 0;

Env::Env(std::shared_ptr<Env> prev_env):
   m_id(s_id++),
   m_prev_env(prev_env)
{}

void Env::put(TokenPtr token, NodePtr symbol)
{
   auto s = std::dynamic_pointer_cast<SymbolNode>(symbol);
   assert(s.get() != nullptr);
   s->set_env(m_id);
   m_table[token] = symbol;
}

bool Env::is_redefine(TokenPtr token) const
{
   auto found = m_table.find(token);
   return found != m_table.end();
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
