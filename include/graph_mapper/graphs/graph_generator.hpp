#pragma once
#include <ranges>

namespace wind::gm
{

template<is_graph GraphT>
constexpr auto generate_graphs() -> std::ranges::view auto
{
  return std::views::iota(0ULL, GraphT::number_of_graphs) | std::views::transform([](size_t i) { return GraphT(i); });
}

}  // namespace wind::gm
