#include "graph_mapper/solvers/maximum_independent_set.hpp"

#include <doctest/doctest.h>

#include "graph_mapper/graphs/graph_generator.hpp"
#include "graph_mapper/graphs/undirected_graph.hpp"

namespace wind::gm
{

TEST_SUITE("maximum_independent_set::maximum_independent_set_size")
{
  TEST_CASE("edge cases")
  {
    SUBCASE("Empty graph")
    {
      auto g = UGraph<5>(0);
      CHECK_EQ(maximum_independent_set_size(g), 5);
    }
    SUBCASE("Complete graph<5>")
    {
      auto g = UGraph<5>(UGraph<5>::number_of_graphs - 1ULL);
      CHECK_EQ(maximum_independent_set_size(g), 1);
    }
  }
}

TEST_SUITE("maximum_independent_set::maximum_independent_set")
{
  TEST_CASE("edge cases")
  {
    SUBCASE("Empty graph")
    {
      auto g = UGraph<5>(0);
      auto solutions = maximum_independent_set(g);
      CHECK_EQ(solutions.size(), 1);
      CHECK_EQ(solutions[0].count(), 5);
    }
    SUBCASE("Complete graph<2>")
    {
      auto g = UGraph<2>(UGraph<2>::number_of_graphs - 1ULL);
      auto solutions = maximum_independent_set(g);
      CHECK_EQ(solutions.size(), 2);
      for (auto& solution : solutions) {
        CHECK_EQ(solution.count(), 1);
      }
    }
    SUBCASE("Complete graph<5>")
    {
      auto g = UGraph<5>(UGraph<5>::number_of_graphs - 1ULL);
      auto solutions = maximum_independent_set(g);
      CHECK_EQ(solutions.size(), 5);
      for (auto& solution : solutions) {
        CHECK_EQ(solution.count(), 1);
      }
    }
  }
}

}  // namespace wind::gm
