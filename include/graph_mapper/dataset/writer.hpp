#pragma once
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string_view>

#include "graph_mapper/dataset/constants.hpp"

namespace wind::gm
{

template<is_graph GraphT>
auto write_ids_to_csv(const std::vector<GraphT>& graphs, std::string_view file_name) -> void
{
  auto ss = std::stringstream();
  ss << "id\n";
  for (const auto& g : graphs) {
    ss << g.id() << "\n";
  }
  auto fs = std::ofstream(dataset_dir / file_name);
  fs << ss.str();
}

}  // namespace wind::gm