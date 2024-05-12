#pragma once
#include <algorithm>
#include <array>
#include <cstdint>
#include <format>
#include <ostream>
#include <ranges>
#include <stack>
#include <string>
#include <vector>

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

  constexpr auto set_edge(this const auto& self, uint32_t v1, uint32_t v2) -> bool { return self.set_edge(v1, v2); }

  constexpr auto has_edge(this const auto& self, uint32_t v1, uint32_t v2) -> bool { return self.has_edge(v1, v2); }

  constexpr auto is_connected(this const auto& self) -> bool
  {
    using type = std::remove_cvref_t<decltype(self)>;

    auto visited = std::array<bool, type::vertices> {false};
    auto s = std::stack<uint32_t> {};
    s.push(0);
    visited[0] = true;

    auto total = 0;
    while (!s.empty()) {
      auto active = s.top();
      s.pop();
      total++;
      for (auto i = 0UL; i < type::vertices; i++) {
        if (i != active && !visited[i] && self.has_edge(active, i)) {
          visited[i] = true;
          s.push(i);
        }
      }
    }
    return total == type::vertices;
  }

  auto to_dot(this const auto& self) -> std::string
  {
    using type = std::remove_cvref_t<decltype(self)>;

    auto edges =
        std::views::cartesian_product(std::views::iota(0UL, type::vertices), std::views::iota(0UL, type::vertices))
        | std::views::filter(
            [&self](auto p)
            { return std::get<0>(p) < std::get<1>(p) && self.has_edge(std::get<0>(p), std::get<1>(p)); })
        | std::views::transform([](auto p) { return std::format("  {} -- {};\n", std::get<0>(p), std::get<1>(p)); })
        | std::views::join | std::views::common;
    return std::format(
        "graph G{} {{\n"
        "  rankdir=LR;\n"
        "  node [shape=circle];\n"
        "  edge [dir=none];\n"
        "  {}\n"
        "}}",
        self.id(),
        std::string {std::begin(edges), std::end(edges)});
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