#include "graph_mapper/solvers/minimum_vertex_cover.hpp"

#include <doctest/doctest.h>

#include "graph_mapper/graphs/graph_generator.hpp"
#include "graph_mapper/graphs/undirected_graph.hpp"

namespace wind::gm
{

TEST_SUITE("minimum_vertex_cover::minimum_vertex_cover_size")
{
  TEST_CASE("edge cases")
  {
    SUBCASE("Empty graph")
    {
      auto g = UGraph<5>(0);
      CHECK_EQ(minimum_vertex_cover_size(g), 0);
    }
    SUBCASE("Complete graph")
    {
      auto g = UGraph<5>(UGraph<5>::number_of_graphs - 1ULL);
      CHECK_EQ(minimum_vertex_cover_size(g), 4);
    }
  }
}

TEST_SUITE("minimum_vertex_cover::minimum_vertex_cover")
{
  TEST_CASE("edge cases")
  {
    SUBCASE("Empty graph")
    {
      auto g = UGraph<5>(0);
      auto solutions = minimum_vertex_cover(g);
      CHECK_EQ(solutions.size(), 1);
      CHECK_EQ(solutions[0].count(), 0);
    }
    SUBCASE("Complete graph")
    {
      auto g = UGraph<5>(UGraph<5>::number_of_graphs - 1ULL);
      auto solutions = minimum_vertex_cover(g);
      CHECK_EQ(solutions.size(), 5);
      for (auto& solution : solutions) {
        CHECK_EQ(solution.count(), 4);
      }
    }
  }
}

}  // namespace wind::gm
