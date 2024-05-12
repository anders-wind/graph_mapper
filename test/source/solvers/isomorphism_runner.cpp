#include <fstream>
#include <ranges>
#include <sstream>

#include "graph_mapper/solvers/isomorphism.hpp"

#include <doctest/doctest.h>

#include "../test_helpers.h"
#include "graph_mapper/graphs/undirected_graph.hpp"

namespace wind::gm
{

TEST_SUITE("isomorphism")
{
  TEST_CASE("dump all base forms" * doctest::skip(true))
  {
    auto graphs = unique_graphs(get_all_base_forms_v2<UGraph<8>>(all_ok));
    std::ranges::sort(graphs, [](const auto& a, const auto& b) { return a.id() < b.id(); });

    auto ss = std::stringstream();
    ss << "id\n";
    for (const auto& g : graphs) {
      ss << g.id() << "\n";
    }
    auto fs = std::ofstream("none_isomorphic_undirected_graphs_of_up_to_size_8.csv");
    fs << ss.str();
  }

  TEST_CASE("dump all base forms of connected_graphs" * doctest::skip(true))
  {
    auto graphs = unique_graphs(get_all_base_forms_v2<UGraph<8>>([](auto g) { return g.is_connected(); }));
    std::ranges::sort(graphs, [](const auto& a, const auto& b) { return a.id() < b.id(); });

    auto ss = std::stringstream();
    ss << "id\n";
    for (const auto& g : graphs) {
      ss << g.id() << "\n";
    }
    auto fs = std::ofstream("none_isomorphic_connected_undirected_graphs_of_up_to_size_8.csv");
    fs << ss.str();
  }
}

}  // namespace wind::gm
