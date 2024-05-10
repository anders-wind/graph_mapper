#include <ranges>
#include <unordered_set>

#include "graph_mapper/solvers/isomorphism.hpp"

#include <doctest/doctest.h>

#include "graph_mapper/graphs/graph_generator.hpp"
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
    auto checker = []<int32_t V>()
    {
      auto unique_graphs = generate_graphs<UGraph<V>>()
          | std::ranges::views::transform([](auto g)
                                          { return base_form(g).id(); })
          | std::ranges::to<std::unordered_set>();
      return unique_graphs.size();
    };

    // https://cw.fel.cvut.cz/b201/_media/courses/b4m33pal/lectures/isomorphism_notes.pdf
    // https://oeis.org/A000088
    SUBCASE("V=1")
    {
      CHECK_EQ(checker.operator()<1>(), 1);
    }
    SUBCASE("V=2")
    {
      CHECK_EQ(checker.operator()<2>(), 2);
    }
    SUBCASE("V=3")
    {
      CHECK_EQ(checker.operator()<3>(), 4);
    }
    SUBCASE("V=4")
    {
      CHECK_EQ(checker.operator()<4>(), 11);
    }
    SUBCASE("V=5")
    {
      CHECK_EQ(checker.operator()<5>(), 34);
    }
    SUBCASE("V=6")
    {
      CHECK_EQ(checker.operator()<6>(), 156);
    }
  }

  TEST_CASE("number of none-isomorphic connected graphs")
  {
    auto checker = []<int32_t V>()
    {
      auto unique_graphs = generate_graphs<UGraph<V>>()
          | std::ranges::views::filter([](auto g) { return g.is_connected(); })
          | std::ranges::views::transform([](auto g)
                                          { return base_form(g).id(); })
          | std::ranges::to<std::unordered_set>();
      return unique_graphs.size();
    };

    // https://cw.fel.cvut.cz/b201/_media/courses/b4m33pal/lectures/isomorphism_notes.pdf
    // https://oeis.org/A001349
    SUBCASE("V=1")
    {
      CHECK_EQ(checker.operator()<1>(), 1);
    }
    SUBCASE("V=2")
    {
      CHECK_EQ(checker.operator()<2>(), 1);
    }
    SUBCASE("V=3")
    {
      CHECK_EQ(checker.operator()<3>(), 2);
    }
    SUBCASE("V=4")
    {
      CHECK_EQ(checker.operator()<4>(), 6);
    }
    SUBCASE("V=5")
    {
      CHECK_EQ(checker.operator()<5>(), 21);
    }
    SUBCASE("V=6")
    {
      CHECK_EQ(checker.operator()<6>(), 112);
    }
  }
}

}  // namespace wind::gm
