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
 * @brief In computer science, the clique problem is the computational problem of finding cliques (subsets of vertices,
 * all adjacent to each other, also called complete subgraphs) in a graph
 *
 */
namespace wind::gm
{

template<is_graph GraphT>
auto is_clique(const GraphT& graph, std::bitset<GraphT::num_vertices> solution) -> bool
{
  for (auto i = 0UL; i < GraphT::num_vertices; i++) {
    for (auto j = i + 1; j < GraphT::num_vertices; j++) {
      if (!graph.has_edge(i, j) && solution[i] && solution[j]) {
        return false;
      }
    }
  }
  return true;
}

template<is_graph GraphT>
auto maximum_clique_size(const GraphT& graph) -> uint32_t
{
  auto max_size = 0UL;
  for (auto i = 1UL; i <= GraphT::num_vertices; i++) {
    auto had_clique = false;
    for (auto solution : generate_all_permutations_with_n_active_bits<GraphT::num_vertices>(i)) {
      if (is_clique(graph, solution)) {
        had_clique = true;
        max_size = i;
        break;
      }
    }

    if (!had_clique) {
      return max_size;
    }
  }

  return max_size;
}

template<is_graph GraphT>
auto maximum_clique(const GraphT& graph) -> std::vector<std::bitset<GraphT::num_vertices>>
{
  auto solution_size = maximum_clique_size(graph);
  if (solution_size == 0) {
    return {};
  }

  return generate_all_permutations_with_n_active_bits<GraphT::num_vertices>(solution_size)
      | std::views::filter([&graph](auto solution) { return is_clique(graph, solution); })
      | std::ranges::to<std::vector>();
}

template<is_graph GraphT>
struct MaximumCliqueSolution
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
auto solve_all_maximum_clique(const std::vector<GraphT>& graphs) -> std::vector<MaximumCliqueSolution<GraphT>>
{
  return graphs
      | std::views::transform(
             [](const auto& g)
             {
               auto solutions = maximum_clique(g);
               return MaximumCliqueSolution<GraphT> {g, solutions.at(0).count(), solutions.size()};
             })
      | std::ranges::to<std::vector>();
}

}  // namespace wind::gm