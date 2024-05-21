#include <format>
#include <string>

#include "graph_mapper/graph_mapper.hpp"

exported_class::exported_class()
    : m_name {std::format("{}", "graph_mapper")}
{
}

auto exported_class::name() const -> char const*
{
  return m_name.c_str();
}
