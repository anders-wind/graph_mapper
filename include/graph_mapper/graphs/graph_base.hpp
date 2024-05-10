#pragma once
#include <array>
#include <cstdint>
#include <ostream>
#include <stack>

#include "graph_mapper/graphs/graph_concepts.hpp"

namespace wind::gm
{

struct Graph
{
public:
  constexpr auto operator==(const Graph& other) const -> bool = default;

  constexpr auto get_vertices(this const auto& self) -> uint32_t
  {
    using type = std::remove_cvref_t<decltype(self)>;
    return type::vertices;
  }

  constexpr auto set_edge(this const auto& self, uint32_t v1, uint32_t v2)
      -> bool
  {
    return self.set_edge(v1, v2);
  }

  constexpr auto has_edge(this const auto& self, uint32_t v1, uint32_t v2)
      -> bool
  {
    return self.has_edge(v1, v2);
  }

  constexpr auto is_connected(this const auto& self) -> bool
  {
    using type = std::remove_cvref_t<decltype(self)>;

    std::array<bool, type::vertices> visited = {false};
    std::stack<uint32_t> s;
    s.push(0);

    auto total = 0;
    while (!s.empty()) {
      auto active = s.top();
      visited[active] = true;
      s.pop();
      total++;
      for (auto i = 0UL; i < type::vertices; i++) {
        if (i != active && !visited[i] && self.has_edge(active, i)) {
          s.push(i);
        }
      }
    }
    return total == type::vertices;
  }
};

static_assert(is_graph<Graph>);

template<is_graph GraphT>
auto operator<<(std::ostream& os, const GraphT& g) -> std::ostream&
{
  auto v = g.get_vertices();
  os << "G(V=" << v << ", ID=" << g.id() << ", E={\n";
  for (auto i = 0UL; i < v; i++) {
    os << "   ";
    for (auto j = 0UL; j < v; j++) {
      os << g.has_edge(i, j) << ", ";
    }
    os << "\n";
  }
  return os << "})";
}

}  // namespace wind::gm