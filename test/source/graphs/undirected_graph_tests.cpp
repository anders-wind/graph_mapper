#include "graph_mapper/graphs/undirected_graph.hpp"

#include <doctest/doctest.h>

namespace wind::gm
{
static_assert(is_graph<UGraph<5>>);
static_assert(UGraph<1>::number_of_graphs == 1);
static_assert(UGraph<2>::number_of_graphs == 2);
static_assert(UGraph<3>::number_of_graphs == 8);
static_assert(UGraph<4>::number_of_graphs == 64);
static_assert(UGraph<5>::number_of_graphs == 1024);
static_assert(UGraph<7>::number_of_graphs == 1ULL << 21);  // 2^21/1024/1024 = 2 MB
static_assert(UGraph<8>::number_of_graphs == 1ULL << 28);  // 2^28/1024/1024 = 256 MB
static_assert(UGraph<9>::number_of_graphs == 1ULL << 36);  // 2^36/1024/1024/1024 = 64 GB
static_assert(UGraph<10>::number_of_graphs == 1ULL << 45);  // 2^45/1024/1024/1024/1024 = 32 TB
static_assert(UGraph<11>::number_of_graphs == 1ULL << 55);  // max, the next is at 66

TEST_SUITE("has_edge")
{
  TEST_CASE("Empty graph")
  {
    auto g = UGraph<5>(0);
    for (auto i = 0UL; i < g.num_vertices; i++) {
      for (auto j = i + 1; j < g.num_vertices; j++) {
        CHECK(!g.has_edge(i, j));
        CHECK(!g.has_edge(j, i));
        CHECK(g.index(i, j) == g.index(j, i));
      }
    }
  }

  TEST_CASE("Fully Connected Graph")
  {
    auto g = UGraph<5>(UGraph<5>::number_of_graphs - 1);  // all ones
    for (auto i = 0UL; i < g.num_vertices; i++) {
      for (auto j = i + 1; j < g.num_vertices; j++) {
        CHECK(g.has_edge(i, j));
        CHECK(g.has_edge(j, i));
      }
    }
  }

  TEST_CASE("General Graph")
  {
    auto g = UGraph<5>(503);
    for (auto i = 0UL; i < g.num_vertices; i++) {
      for (auto j = i + 1; j < g.num_vertices; j++) {
        CHECK(g.has_edge(i, j) == g.has_edge(i, j));
      }
    }
  }
}

TEST_SUITE("index")
{
  TEST_CASE("Testing index is same for (i,j) and (j,i)")
  {
    auto g = UGraph<5>(0);
    for (auto i = 0UL; i < g.num_vertices; i++) {
      for (auto j = i + 1; j < g.num_vertices; j++) {
        CHECK(g.index(i, j) == g.index(j, i));
      }
    }
  }
}
}  // namespace wind::gm