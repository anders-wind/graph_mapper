#include <ranges>

#include "graph_mapper/solvers/minimum_vertex_cover.hpp"

#include <doctest/doctest.h>

#include "graph_mapper/dataset/loader.hpp"
#include "graph_mapper/dataset/writer.hpp"
#include "graph_mapper/graphs/undirected_graph.hpp"

namespace wind::gm
{
namespace
{

template<uint32_t V>
struct integer
{
  constexpr static auto v = V;
};
}  // namespace

TEST_SUITE("minimum_vertex_cover")
{
  TEST_CASE_TEMPLATE("dump all minimum_vertex_cover dataset" * doctest::skip(true),
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
    auto graphs = load_none_isomorphic_connected_undirected_graphs_of_up_to_size_n<V::v>();
    auto solutions = solve_all_minimum_vertex_cover(graphs);
    write_solution_to_csv(solutions,
                          std::format("minimum_vertex_cover_of_undirected_connected_graphs_size_{}.csv", V::v));
  }
}

}  // namespace wind::gm
