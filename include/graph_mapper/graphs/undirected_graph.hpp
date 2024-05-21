#pragma once
#include <bitset>
#include <cstdint>

#include "graph_mapper/graphs/graph_base.hpp"
#include "graph_mapper/graphs/graph_concepts.hpp"

namespace wind::gm
{

template<uint32_t V>
  requires(V > 0)
struct UndirectedGraph : public Graph
{
  using self_t = UndirectedGraph<V>;

  constexpr static uint32_t num_vertices = V;
  constexpr static uint32_t max_edges = V == 1 ? 0 : ((V * (V - 1)) / 2);
  constexpr static size_t number_of_graphs = 1ULL << self_t::max_edges;
  constexpr static bool is_undirected = true;
  constexpr static auto vertices = []() consteval -> std::array<uint32_t, num_vertices>
  {
    auto res = std::array<uint32_t, num_vertices> {};
    for (auto i = uint32_t(0); i < num_vertices; i++) {
      res[i] = i;
    }
    return res;
  }();
  constexpr static auto all_vertex_pairs = []() consteval -> std::array<edge, self_t::max_edges>
  {
    if constexpr (V == 1) {
      return {};
    } else {
      auto res = std::array<edge, self_t::max_edges> {};
      for (auto i = uint32_t(0); i < num_vertices; i++) {
        for (auto j = i + 1; j < num_vertices; j++) {
          res[j * (j - 1UL) / 2UL + i] = {i, j};
        }
      }
      return res;
    }
  }();

  std::bitset<self_t::max_edges> edge_bits;

  /**
   * edge_combination_bit is the number describing the bits that represent the
   * activated edges.
   */
  UndirectedGraph(uint64_t edge_combination_bit)
      : edge_bits(std::bitset<self_t::max_edges>(edge_combination_bit))
  {
  }

  constexpr auto operator==(const UndirectedGraph& other) const -> bool = default;

  constexpr auto id() const -> uint64_t
  {
    if constexpr (V == 1) {
      return 0;
    } else {
      return this->edge_bits.to_ullong();
    }
  }

  constexpr auto index(uint32_t v1, uint32_t v2) const -> size_t
  {
    auto vlow = std::min(v1, v2);
    auto vhigh = std::max(v1, v2);
    return vhigh * (vhigh - 1UL) / 2UL + vlow;
  }

  constexpr void set_edge(uint32_t v1, uint32_t v2, bool val = true)
  {
    if (v1 == v2) {
      return;
    }
    this->edge_bits.set(this->index(v1, v2), val);
  }

  constexpr auto has_edge(uint32_t v1, uint32_t v2) const -> bool
  {
    if (v1 == v2) {
      return false;
    }
    return this->edge_bits[this->index(v1, v2)];
  }

  constexpr auto connected_to(uint32_t from) const -> std::ranges::view auto
  {
    return self_t::vertices
        | std::views::filter([this, from](auto to) { return from != to && this->has_edge(from, to); });
  }

  constexpr auto edges() const -> std::ranges::view auto
  {
    return all_vertex_pairs
        | std::views::filter(
               [this](auto p)
               {
                 auto [v1, v2] = p;
                 return v1 < v2 && this->has_edge(v1, v2);
               });
  }
};

template<int32_t V>
using UGraph = UndirectedGraph<V>;

}  // namespace wind::gm