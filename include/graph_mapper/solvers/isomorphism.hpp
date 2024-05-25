#pragma once
#include <algorithm>
#include <array>
#include <cstdint>
#include <optional>
#include <span>
#include <unordered_set>
#include <vector>

#include "graph_mapper/graphs/graph_base.hpp"
#include "graph_mapper/graphs/graph_concepts.hpp"
#include "graph_mapper/graphs/graph_generator.hpp"
#include "graph_mapper/solvers/permutations.hpp"

namespace wind::gm
{

template<is_graph GraphT>
constexpr auto swap(const GraphT& g, uint32_t v1, uint32_t v2) -> GraphT
{
  auto res = g;

  if (v1 == v2) {
    return res;
  }

  for (auto i = 0UL; i < GraphT::num_vertices; i++) {
    res.set_edge(i, v2, g.has_edge(i, v1));
    res.set_edge(i, v1, g.has_edge(i, v2));
  }

  if constexpr (GraphT::is_undirected) {
    res.set_edge(v1, v2, g.has_edge(v1, v2));
  }

  return res;
}

template<is_graph GraphT>
constexpr auto base_form(const GraphT& base, uint32_t current_index = 0) -> GraphT
{
  if (current_index == GraphT::num_vertices) {
    return base;
  }

  auto lowest_id_graph = base_form(base, current_index + 1);
  for (auto i = current_index + 1; i < GraphT::num_vertices; i++) {
    auto swapped = base_form(swap(base, current_index, i), current_index + 1);
    if (swapped.id() < lowest_id_graph.id()) {
      lowest_id_graph = swapped;
    }
  }

  return lowest_id_graph;
}

template<is_graph GraphT>
constexpr auto get_all_graphs_with_same_id(const GraphT& base,
                                           uint32_t current_index,
                                           std::unordered_set<uint64_t>& out) -> void
{
  if (current_index == GraphT::num_vertices) {
    out.emplace(base.id());
    return;
  }

  if (!out.contains(base.id())) {
    get_all_graphs_with_same_id(base, current_index + 1, out);

    for (auto i = current_index + 1; i < GraphT::num_vertices; i++) {
      get_all_graphs_with_same_id(swap(base, current_index, i), current_index + 1, out);
    }
  }
}

template<is_graph GraphT>
auto get_all_graphs_with_same_id(const GraphT& base) -> std::vector<GraphT>
{
  auto out = std::unordered_set<uint64_t> {};
  get_all_graphs_with_same_id(base, 0, out);
  return out | std::views::transform([](auto id) { return GraphT(id); }) | std::ranges::to<std::vector>();
}

// Assumes all graphs in the group have the same base form. IE found with get_all_graphs_with_same_id
template<is_graph GraphT>
auto get_base_form_of_group(std::span<const GraphT> group) -> GraphT
{
  return *std::ranges::min_element(group, [](const auto& a, const auto& b) { return a.id() < b.id(); });
}

template<typename GraphT>
auto get_all_base_forms_v2(auto filter) -> std::vector<GraphT>
{
  auto cache = std::vector<std::optional<GraphT>>(GraphT::number_of_graphs);
  for (const auto& g : generate_graphs<GraphT>() | std::views::filter(filter)) {
    if (cache[g.id()]) {
      continue;
    }

    auto group = get_all_graphs_with_same_id(g);
    auto base = get_base_form_of_group<GraphT>(group);
    for (const auto& g_inner : group) {
      cache[g_inner.id()] = base;
    }
  }

  return cache | std::views::filter([](const auto& g) { return g.has_value(); })
      | std::views::transform([](const auto& g) { return g.value(); }) | std::ranges::to<std::vector>();
}

template<typename GraphT, bool ShouldBeConnected>
auto get_all_base_forms_v3() -> std::vector<GraphT>
{
  if constexpr (GraphT::num_vertices == 1) {
    return {GraphT(0)};
  } else {
    auto prev_level = get_all_base_forms_v3<typename GraphT::graph_with_one_less_vertex_t, ShouldBeConnected>();

    auto new_level = std::vector<GraphT> {};
    for (const auto& g : prev_level) {
      auto g_with_extra_vertex = g.with_added_vertex();

      for (auto to_connect_to : generate_all_permutations<GraphT::num_vertices - 1>()) {
        if (to_connect_to.count() == 0) {
          if constexpr (!ShouldBeConnected) {
            new_level.emplace_back(base_form(g_with_extra_vertex));
          }
          continue;
        }

        auto g_with_edges_to_new_vertex = g_with_extra_vertex;
        for (auto i = 0UL; i < GraphT::num_vertices - 1; i++) {
          g_with_edges_to_new_vertex.set_edge(i, GraphT::num_vertices - 1, to_connect_to[i]);
        }
        new_level.emplace_back(base_form(g_with_edges_to_new_vertex));
      }
    }
    return unique_graphs(new_level);
  }
}

template<is_graph GraphT>
auto get_all_none_isomorphic_graphs() -> std::vector<GraphT>
{
  auto res = unique_graphs(get_all_base_forms_v2<GraphT>([](const auto&) { return true; }));
  // auto res = unique_graphs(get_all_base_forms_v3<GraphT, false>());
  std::ranges::sort(res, [](const auto& a, const auto& b) { return a.id() < b.id(); });
  return res;
}

template<is_graph GraphT>
auto get_all_none_isomorphic_connected_graphs() -> std::vector<GraphT>
{
  auto res = unique_graphs(get_all_base_forms_v2<GraphT>([](const auto& g) { return g.is_connected(); }));
  // auto res = unique_graphs(get_all_base_forms_v3<GraphT, true>());
  std::ranges::sort(res, [](const auto& a, const auto& b) { return a.id() < b.id(); });
  return res;
}

}  // namespace wind::gm
