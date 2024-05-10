#pragma once

#include <concepts>

namespace wind::gm
{

template<typename T>
concept is_graph = requires(T& g) {
  {
    g.get_vertices()
  } -> std::same_as<uint32_t>;
  {
    g.has_edge(0, 0)
  } -> std::same_as<bool>;
  {
    g.set_edge(0, 0)
  };
};

}  // namespace wind::gm