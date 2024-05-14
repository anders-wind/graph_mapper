#include <ranges>

#include "graph_mapper/solvers/isomorphism.hpp"

#include <doctest/doctest.h>

#include "graph_mapper/dataset/writer.hpp"
#include "graph_mapper/graphs/undirected_graph.hpp"

namespace wind::gm
{
template<uint32_t V>
struct integer
{
  constexpr static auto v = V;
};

TEST_SUITE("isomorphism")
{
  TEST_CASE_TEMPLATE("dump all base forms" * doctest::skip(true),
                     V,
                     integer<1>,
                     integer<2>,
                     integer<3>,
                     integer<4>,
                     integer<5>,
                     integer<6>,
                     integer<7>,
                     integer<8>)
  {
    auto graphs = get_all_none_isomorphic_graphs<UGraph<V::v>>();
    write_ids_to_csv(graphs, std::format("none_isomorphic_undirected_graphs_of_up_to_size_{}.csv", V::v));
  }

  TEST_CASE_TEMPLATE("dump all base forms of connected_graphs" * doctest::skip(true),
                     V,
                     integer<1>,
                     integer<2>,
                     integer<3>,
                     integer<4>,
                     integer<5>,
                     integer<6>,
                     integer<7>,
                     integer<8>)
  {
    auto graphs = get_all_none_isomorphic_connected_graphs<UGraph<V::v>>();
    write_ids_to_csv(graphs, std::format("none_isomorphic_connected_undirected_graphs_of_up_to_size_{}.csv", V::v));
  }
}

}  // namespace wind::gm
