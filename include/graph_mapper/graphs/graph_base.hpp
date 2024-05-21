#pragma once
#include <algorithm>
#include <array>
#include <cstdint>
#include <format>
#include <ostream>
#include <ranges>
#include <stack>
#include <string>
#include <unordered_set>
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
    return type::num_vertices;
  }

  constexpr auto set_edge(this const auto& self, uint32_t v1, uint32_t v2) -> bool { return self.set_edge(v1, v2); }

  constexpr auto has_edge(this const auto& self, uint32_t v1, uint32_t v2) -> bool { return self.has_edge(v1, v2); }

  constexpr auto is_connected(this const auto& self) -> bool
  {
    using type = std::remove_cvref_t<decltype(self)>;

    auto visited = std::array<bool, type::num_vertices> {false};
    auto s = std::stack<uint32_t> {};
    s.push(0);
    visited[0] = true;

    auto total = 0;
    while (!s.empty()) {
      auto active = s.top();
      s.pop();
      total++;
      for (auto i : self.connected_to(active))
        if (i != active && !visited[i]) {
          visited[i] = true;
          s.push(i);
        }
    }
    return total == type::num_vertices;
  }

  auto to_dot(this const auto& self) -> std::string
  {
    using type = std::remove_cvref_t<decltype(self)>;

    auto edges = self.edges()
        | std::views::transform([](auto edge) { return std::format("  {} -- {};\n", edge.v1, edge.v2); })
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

template<is_graph GraphT>
auto operator<<(std::ostream& os, const GraphT& g) -> std::ostream&
{
  constexpr auto v = GraphT::num_vertices;
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

template<typename GraphT>
constexpr auto unique_graphs(const std::vector<GraphT>& graphs) -> std::vector<GraphT>
{
  auto ids = graphs | std::views::transform([](auto g) { return g.id(); });
  auto unique_ids = std::unordered_set<uint64_t>(std::begin(ids), std::end(ids));
  auto rng = unique_ids | std::views::transform([](auto id) { return GraphT(id); });
  return std::vector<GraphT>(std::begin(rng), std::end(rng));
}

}  // namespace wind::gm