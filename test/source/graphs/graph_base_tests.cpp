#include <iostream>

#include "graph_mapper/graphs/graph_base.hpp"

#include <doctest/doctest.h>

#include "graph_mapper/graphs/graph_generator.hpp"
#include "graph_mapper/graphs/undirected_graph.hpp"

namespace wind::gm
{

TEST_SUITE("graph_generator")
{
  TEST_CASE("is_connected")
  {
    auto g = UGraph<3>(0);
    CHECK_EQ(g.is_connected(), false);

    g = UGraph<3>(3);
    CHECK_EQ(g.is_connected(), true);

    g = UGraph<3>(7);
    CHECK_EQ(g.is_connected(), true);
  }

  TEST_CASE("print all graphs of size 3" * doctest::skip())
  {
    for (const auto& g : generate_graphs<UGraph<3>>()) {
      std::cout << g.to_dot() << std::endl;
    }
  }
}

}  // namespace wind::gm