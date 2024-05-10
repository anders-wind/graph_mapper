#pragma once
#include <bitset>
#include <cstdint>

#include "graph_mapper/graphs/graph_base.hpp"

namespace wind::gm
{

template<int32_t V>
  requires(V > 0)
struct UndirectedGraph : public Graph
{
  using self_t = UndirectedGraph<V>;

  constexpr static auto vertices = V;
  constexpr static auto max_edges = V == 1 ? 0 : ((V * (V - 1)) / 2);
  constexpr static auto number_of_graphs = 1ULL << self_t::max_edges;
  constexpr static auto is_undirected = true;

  std::bitset<self_t::max_edges> edges;

  /**
   * edge_combination_bit is the number describing the bits that represent the
   * activated edges.
   */
  UndirectedGraph(uint64_t edge_combination_bit)
      : edges(std::bitset<self_t::max_edges>(edge_combination_bit))
  {
  }

  constexpr auto operator==(const UndirectedGraph& other) const
      -> bool = default;

  constexpr auto id() const -> uint64_t { return this->edge_bits(); }

  constexpr auto index(uint32_t v1, uint32_t v2) const -> size_t
  {
    auto vlow = std::min(v1, v2);
    auto vhigh = std::max(v1, v2);
    return vhigh * (vhigh - 1ULL) / 2ULL + vlow;
  }

  constexpr void set_edge(uint32_t v1, uint32_t v2, bool val = true)
  {
    if (v1 == v2) {
      return;
    }
    this->edges.set(this->index(v1, v2), val);
  }

  constexpr auto has_edge(uint32_t v1, uint32_t v2) const -> bool
  {
    if (v1 == v2) {
      return false;
    }
    return this->edges[this->index(v1, v2)];
  }

  constexpr auto edge_bits() const -> uint64_t
  {
    if constexpr (V == 1) {
      return 0;
    } else {
      return this->edges.to_ullong();
    }
  }
};

template<int32_t V>
using UGraph = UndirectedGraph<V>;

}  // namespace wind::gm