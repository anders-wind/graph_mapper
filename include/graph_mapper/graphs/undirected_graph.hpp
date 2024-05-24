#pragma once
#include <bitset>
#include <cstdint>

#include "graph_mapper/graphs/graph_base.hpp"
#include "graph_mapper/graphs/graph_concepts.hpp"

namespace wind::gm
{

template<uint32_t V>
  requires(V >= 0)
struct UndirectedGraph : public Graph
{
  using self_t = UndirectedGraph<V>;

  constexpr static auto num_vertices = V;
  constexpr static auto max_edges = V == 1 ? 0 : ((V * (V - 1)) / 2);
  constexpr static auto number_of_graphs = 1ULL << self_t::max_edges;
  constexpr static auto is_undirected = true;
  constexpr static auto vertices = []() consteval -> std::array<uint32_t, self_t::num_vertices>
  {
    auto res = std::array<uint32_t, self_t::num_vertices> {};
    for (auto i = 0UL; i < self_t::num_vertices; i++) {
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
      for (auto i = 0UL; i < self_t::num_vertices; i++) {
        for (auto j = i + 1; j < self_t::num_vertices; j++) {
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

  constexpr auto num_edges() const -> uint32_t { return static_cast<uint32_t>(this->edge_bits.count()); }

  constexpr auto degree(uint32_t v) const -> uint32_t
  {
    return static_cast<uint32_t>(
        std::ranges::count_if(self_t::vertices, [this, v](auto i) { return this->has_edge(v, i); }));
  }

  constexpr auto connected_to(uint32_t from) const -> std::ranges::view auto
  {
    return self_t::vertices | std::views::filter([this, from](auto to) { return this->has_edge(from, to); });
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

  constexpr auto with_added_vertex() const -> UndirectedGraph<V + 1>
  {
    auto res = UGraph<V + 1>(0);
    for (auto i = 0UL; i < V; i++) {
      for (auto j = i + 1; j < V; j++) {
        res.set_edge(i, j, this->has_edge(i, j));
      }
    }
    return res;
  }

  using graph_with_one_less_vertex_t =
      std::conditional_t<num_vertices == 1, UndirectedGraph<0>, UndirectedGraph<num_vertices - 1>>;
};

template<>
struct UndirectedGraph<0>
{
};

template<int32_t V>
using UGraph = UndirectedGraph<V>;

}  // namespace wind::gm