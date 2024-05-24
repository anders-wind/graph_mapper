#pragma once
#include <string>
#include <string_view>

namespace wind::gm
{
template<typename T>
concept is_solution = requires(T t) {
  {
    t.to_csv_row()
  } -> std::same_as<std::string>;
  {
    T::csv_header()
  } -> std::same_as<std::string_view>;
};
}