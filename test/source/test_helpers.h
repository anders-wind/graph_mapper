#pragma once
#include <ranges>
#include <unordered_set>
#include <vector>

namespace wind::gm
{
constexpr auto all_ok = [](const auto&) { return true; };

template<typename GraphT>
constexpr auto unique_graphs(const std::vector<GraphT>& graphs) -> std::vector<GraphT>
{
  auto unique_ids =
      graphs | std::views::transform([](auto g) { return g.id(); }) | std::ranges::to<std::unordered_set>();
  return unique_ids | std::views::transform([](auto id) { return GraphT(id); }) | std::ranges::to<std::vector>();
}

}  // namespace wind::gm