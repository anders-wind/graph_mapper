#pragma once
#include <array>
#include <bitset>
#include <iostream>
#include <stack>

#include <stdint.h>

namespace wind::gm
{

struct Graph
{
public:
  constexpr auto vertices(this const auto& self) -> int32_t
  {
    return self.vertices();
  }

  constexpr auto has_edge(this const auto& self, int32_t v1, int32_t v2) -> bool
  {
    return self.has_edge(v1, v2);
  }

  constexpr auto is_connected(this const auto& self) -> bool
  {
    using type = std::remove_cvref_t<decltype(self)>;

    std::array<bool, vertices()> visited = {false};
    std::stack<int> s;
    s.push(0);

    auto total = 0;
    while (!s.empty() && total != type::vertices()) {
      auto active = s.top();
      visited[active] = true;
      s.pop();
      total++;
      for (auto i = 0; i < type::vertices(); i++) {
        if (i != active && !visited[i] && self.has_edge(active, i)) {
          s.push(i);
        }
      }
    }
    return total == type::vertices();
  }
};

auto operator<<(std::ostream& os, const Graph& obj) -> std::ostream&
{
  auto v = obj.vertices();
  os << "G(V=" << v << ", E={" << std::endl;
  for (auto i = 0; i < v; i++) {
    os << "   ";
    for (auto j = 0; j < v; j++) {
      os << obj.has_edge(i, j) << ", ";
    }
    os << std::endl;
  }
  return os << "})";
}

}  // namespace wind::gm