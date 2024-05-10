#pragma once
#include <array>
#include <cstdint>
#include <optional>

#include "graph_mapper/graphs/graph_concepts.hpp"

namespace wind::gm
{

template<is_graph GraphT>
constexpr auto swap(const GraphT& g, uint32_t v1, uint32_t v2) -> GraphT
{
  auto res = g;

  if (v1 == v2) {
    return res;
  }

  for (auto i = 0UL; i < GraphT::vertices; i++) {
    res.set_edge(i, v2, g.has_edge(i, v1));
    res.set_edge(i, v1, g.has_edge(i, v2));
  }

  if constexpr (GraphT::is_undirected) {
    res.set_edge(v1, v2, g.has_edge(v1, v2));
  }

  return res;
}

template<is_graph GraphT>
constexpr auto base_form(const GraphT& base, uint32_t current_index = 0)
    -> GraphT
{
  if (current_index == GraphT::vertices) {
    return base;
  }

  auto lowest_id_graph = base_form(base, current_index + 1);
  for (auto i = current_index + 1; i < GraphT::vertices; i++) {
    auto swapped = base_form(swap(base, current_index, i), current_index + 1);
    if (swapped.id() < lowest_id_graph.id()) {
      lowest_id_graph = swapped;
    }
  }

  return lowest_id_graph;
}

}  // namespace wind::gm
