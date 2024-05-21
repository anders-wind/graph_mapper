#pragma once
#include <bitset>

#include <tl/generator.hpp>

namespace wind::gm
{

template<uint64_t N>
auto generate_all_permutations_with_n_active_bits(std::bitset<N> base, size_t start_from, size_t k)
    -> tl::generator<std::bitset<N>>
{
  if (k == 0) {
    co_yield base;
    co_return;
  }
  if (start_from >= N) {
    co_return;
  }
  if (k > N - start_from) {
    co_return;
  }

  for (auto solution : generate_all_permutations_with_n_active_bits<N>(base, start_from + 1, k)) {
    co_yield solution;
  }
  base.set(start_from);
  for (auto solution : generate_all_permutations_with_n_active_bits<N>(base, start_from + 1, k - 1)) {
    co_yield solution;
  }
}

template<uint64_t N>
auto generate_all_permutations_with_n_active_bits(size_t k) -> tl::generator<std::bitset<N>>
{
  for (auto solution : generate_all_permutations_with_n_active_bits(std::bitset<N>(), 0, k)) {
    co_yield solution;
  }
}

}  // namespace wind::gm
