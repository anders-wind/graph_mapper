#pragma once
#include <bitset>
#include <cstdint>
#include <format>
#include <ranges>
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
auto is_independent_set(const GraphT& graph, std::bitset<GraphT::num_vertices> solution) -> bool
{
  for (auto i = 0UL; i < GraphT::num_vertices; i++) {
    for (auto j = i + 1; j < GraphT::num_vertices; j++) {
      if (graph.has_edge(i, j) && solution[i] && solution[j]) {
        return false;
      }
    }
  }
  return true;
}

template<is_graph GraphT>
auto maximum_independent_set_size(const GraphT& graph) -> uint32_t
{
  for (auto i = 0UL; i <= GraphT::num_vertices; i++) {
    auto had_independent_set = false;
    for (auto solution : generate_all_permutations_with_n_active_bits<GraphT::num_vertices>(i)) {
      if (is_independent_set(graph, solution)) {
        had_independent_set = true;
        break;
      }
    }

    if (!had_independent_set) {
      return i - 1;
    }
  }

  return GraphT::num_vertices;
}

template<is_graph GraphT>
auto maximum_independent_set(const GraphT& graph) -> std::vector<std::bitset<GraphT::num_vertices>>
{
  auto solution_size = maximum_independent_set_size(graph);
  return generate_all_permutations_with_n_active_bits<GraphT::num_vertices>(solution_size)
      | std::views::filter([&graph](auto solution) { return is_independent_set(graph, solution); })
      | std::ranges::to<std::vector>();
}

template<is_graph GraphT>
struct MaximumIndependentSetSolution
{
  GraphT g;
  size_t maximum_size;
  size_t number_of_solutions;

  static auto csv_header() -> std::string_view { return "id,maximum_size,number_of_solutions\n"; }
  auto to_csv_row() const -> std::string
  {
    return std::format("{},{},{}\n", g.id(), maximum_size, number_of_solutions);
  }
};

template<is_graph GraphT>
auto solve_all_maximum_independent_set(const std::vector<GraphT>& graphs)
    -> std::vector<MaximumIndependentSetSolution<GraphT>>
{
  return graphs
      | std::views::transform(
             [](const auto& g)
             {
               auto solutions = maximum_independent_set(g);
               return MaximumIndependentSetSolution<GraphT> {g, solutions.at(0).count(), solutions.size()};
             })
      | std::ranges::to<std::vector>();
}

}  // namespace wind::gm