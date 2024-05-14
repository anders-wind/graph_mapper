#pragma once

#include <concepts>

namespace wind::gm
{

struct edge
{
  uint32_t v1;
  uint32_t v2;
};

template<typename T>
concept is_graph = requires(T& g) {
  T::num_vertices;
  T::number_of_graphs;
  T::max_edges;
  T::vertices;
  T::all_vertex_pairs;
  {
    g.has_edge(0, 0)
  } -> std::same_as<bool>;
  {
    g.set_edge(0, 0)
  };
  {
    g.edges()
  } -> std::ranges::view;
  {
    g.connected_to(0UL)
  } -> std::ranges::view;
};

}  // namespace wind::gm