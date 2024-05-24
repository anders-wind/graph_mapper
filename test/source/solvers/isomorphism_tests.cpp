#include "graph_mapper/solvers/isomorphism.hpp"

#include <doctest/doctest.h>

#include "graph_mapper/graphs/undirected_graph.hpp"

namespace wind::gm
{

static_assert(is_graph<UGraph<5>>);

TEST_SUITE("isomorphism::base_id")
{
  TEST_CASE("Empty graph")
  {
    auto g = UGraph<5>(0);
    CHECK_EQ(base_form(g), g);
  }

  TEST_CASE("Common base forms")
  {
    for (auto i : {0, 1, 3, 7}) {
      auto g = UGraph<5>(static_cast<uint64_t>(i));
      CHECK_EQ(base_form(g), g);
    }
  }

  TEST_CASE("number of none-isomorphic graphs")
  {
    // https://cw.fel.cvut.cz/b201/_media/courses/b4m33pal/lectures/isomorphism_notes.pdf
    // https://oeis.org/A000088
    SUBCASE("V=1")
    {
      CHECK_EQ(get_all_none_isomorphic_graphs<UGraph<1>>().size(), 1);
    }
    SUBCASE("V=2")
    {
      CHECK_EQ(get_all_none_isomorphic_graphs<UGraph<2>>().size(), 2);
    }
    SUBCASE("V=3")
    {
      CHECK_EQ(get_all_none_isomorphic_graphs<UGraph<3>>().size(), 4);
    }
    SUBCASE("V=4")
    {
      CHECK_EQ(get_all_none_isomorphic_graphs<UGraph<4>>().size(), 11);
    }
    SUBCASE("V=5")
    {
      CHECK_EQ(get_all_none_isomorphic_graphs<UGraph<5>>().size(), 34);
    }
    SUBCASE("V=6")
    {
      CHECK_EQ(get_all_none_isomorphic_graphs<UGraph<6>>().size(), 156);
    }
    // SUBCASE("V=7")  // fast with Release
    // {
    //   CHECK_EQ(get_all_none_isomorphic_graphs<UGraph<7>>().size(), 1044ULL);
    // }
    // SUBCASE("V=8")  // possible with Release
    // {
    //   CHECK_EQ(get_all_none_isomorphic_graphs<UGraph<8>>().size(), 12346ULL);
    // }
    // SUBCASE("V=9")
    // {
    //   CHECK_EQ(get_all_none_isomorphic_graphs<UGraph<9>>().size(), 274668ULL);  // 268KB
    // }
    // SUBCASE("V=10")
    // {
    //   CHECK_EQ(get_all_none_isomorphic_graphs<UGraph<10>>().size(), 12005168ULL); // 11MB
    // }
  }

  TEST_CASE("number of none-isomorphic connected graphs")
  {
    // https://cw.fel.cvut.cz/b201/_media/courses/b4m33pal/lectures/isomorphism_notes.pdf
    // https://oeis.org/A001349
    SUBCASE("V=1")
    {
      CHECK_EQ(get_all_none_isomorphic_connected_graphs<UGraph<1>>().size(), 1);
    }
    SUBCASE("V=2")
    {
      CHECK_EQ(get_all_none_isomorphic_connected_graphs<UGraph<2>>().size(), 1);
    }
    SUBCASE("V=3")
    {
      CHECK_EQ(get_all_none_isomorphic_connected_graphs<UGraph<3>>().size(), 2);
    }
    SUBCASE("V=4")
    {
      CHECK_EQ(get_all_none_isomorphic_connected_graphs<UGraph<4>>().size(), 6);
    }
    SUBCASE("V=5")
    {
      CHECK_EQ(get_all_none_isomorphic_connected_graphs<UGraph<5>>().size(), 21);
    }
    SUBCASE("V=6")
    {
      CHECK_EQ(get_all_none_isomorphic_connected_graphs<UGraph<6>>().size(), 112);
    }
    // SUBCASE("V=7")  // fast with Release
    // {
    //   CHECK_EQ(get_all_none_isomorphic_connected_graphs<UGraph<7>>().size(), 853);
    // }
    // SUBCASE("V=8") // possible with Release
    // {
    //   CHECK_EQ(get_all_none_isomorphic_connected_graphs<UGraph<8>>().size(), 11117);
    // }
    // SUBCASE("V=9")
    // {
    //   CHECK_EQ(get_all_none_isomorphic_connected_graphs<UGraph<9>>().size(), 261080ULL); // 254KB
    // }
    // SUBCASE("V=10")
    // {
    //   CHECK_EQ(get_all_none_isomorphic_connected_graphs<UGraph<10>>().size(), 11716571ULL); // 11MB
    // }
  }

  TEST_CASE("get_all_graphs_with_same_id")
  {
    SUBCASE("edge cases")
    {
      auto g = UGraph<5>(0);
      auto graphs = get_all_graphs_with_same_id(g);
      CHECK_EQ(graphs.size(), 1ULL);
      CHECK_EQ(graphs[0], g);

      g = UGraph<5>(UGraph<5>::number_of_graphs - 1);
      graphs = get_all_graphs_with_same_id(g);
      CHECK_EQ(graphs.size(), 1ULL);
      CHECK_EQ(graphs[0], g);
    }

    SUBCASE("one edge")
    {
      auto graphs = get_all_graphs_with_same_id(UGraph<5>(1));
      CHECK_EQ(graphs.size(), UGraph<5>::max_edges);
    }

    SUBCASE("n-1 edges")
    {
      auto graphs = get_all_graphs_with_same_id(UGraph<5>(UGraph<5>::number_of_graphs - 2));
      CHECK_EQ(graphs.size(), UGraph<5>::max_edges);
    }
  }
}

}  // namespace wind::gm
