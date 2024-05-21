#pragma once
#include <bitset>
#include <cstdint>
#include <vector>

#include "graph_mapper/graphs/graph_concepts.hpp"
#include "graph_mapper/graphs/graph_generator.hpp"
#include "graph_mapper/solvers/permutations.hpp"

/**
 * @brief In graph theory, a vertex cover (sometimes node cover) of a graph is a set of vertices that includes at least
 * one endpoint of every edge of the graph.
 *
 */
namespace wind::gm
{

template<is_graph GraphT>
auto is_vertex_cover(const GraphT& graph, std::bitset<GraphT::num_vertices> solution) -> bool
{
  for (auto i = 0UL; i < GraphT::num_vertices; i++) {
    for (auto j = i + 1; j < GraphT::num_vertices; j++) {
      if (graph.has_edge(i, j) && !solution[i] && !solution[j]) {
        return false;
      }
    }
  }
  return true;
}

template<is_graph GraphT>
auto minimum_vertex_cover_size(const GraphT& graph) -> uint32_t
{
  //   auto minimum_size = std::min(0LL, staticGraphT::num_vertices - graph.edge_bits.count());

  for (auto i = 0UL; i < GraphT::num_vertices; i++) {
    for (auto solution : generate_all_permutations_with_n_active_bits<GraphT::num_vertices>(i)) {
      if (is_vertex_cover(graph, solution)) {
        return i;
      }
    }
  }
  return GraphT::num_vertices;
}

template<is_graph GraphT>
auto minimum_vertex_cover(const GraphT& graph) -> std::vector<std::bitset<GraphT::num_vertices>>
{
  auto solution_size = minimum_vertex_cover_size(graph);

  auto solutions = std::vector<std::bitset<GraphT::num_vertices>> {};
  for (auto solution : generate_all_permutations_with_n_active_bits<GraphT::num_vertices>(solution_size)) {
    if (is_vertex_cover(graph, solution)) {
      solutions.emplace_back(solution);
    }
  }

  return solutions;
}

}  // namespace wind::gm