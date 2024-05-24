#include <ranges>

#include "graph_mapper/solvers/maximum_independent_set.hpp"

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

TEST_SUITE("maximum_independent_set")
{
  TEST_CASE_TEMPLATE("dump all maximum_independent_set dataset" * doctest::skip(false),
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
    auto solutions = solve_all_maximum_independent_set(graphs);
    write_solution_to_csv(solutions,
                          std::format("maximum_independent_set_of_undirected_connected_graphs_size_{}.csv", V::v));
  }
}

}  // namespace wind::gm
