#pragma once
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string_view>

namespace wind::gm
{
#if defined(GM_DATA_DIR)
static const auto dataset_dir = std::filesystem::path {GM_DATA_DIR};
#endif

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