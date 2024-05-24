#pragma once
#include <fstream>
#include <vector>

#include "graph_mapper/dataset/constants.hpp"
#include "graph_mapper/graphs/undirected_graph.hpp"

namespace wind::gm
{

struct RawDataset
{
  std::vector<std::string> columns;
  std::vector<std::vector<std::string>> data;
};

inline auto load_csv(const std::filesystem::path& file_name) -> RawDataset
{
  auto fs = std::ifstream(file_name);
  auto dataset = RawDataset();

  if (!fs.is_open()) {
    throw std::runtime_error("Could not open file");
  }

  auto line = std::string();
  std::getline(fs, line);
  auto ss = std::stringstream(line);
  auto column = std::string();
  while (std::getline(ss, column, ',')) {
    dataset.columns.emplace_back(column);
  }

  while (std::getline(fs, line)) {
    ss = std::stringstream(line);
    auto row = std::vector<std::string>();
    while (std::getline(ss, column, ',')) {
      row.emplace_back(column);
    }
    dataset.data.emplace_back(row);
  }

  return dataset;
}

template<uint32_t V>
auto load_graph_list(const std::string& file_name) -> std::vector<UGraph<V>>
{
  auto dataset = load_csv(dataset_dir / file_name);
  auto graphs = std::vector<UGraph<V>>();
  graphs.reserve(dataset.data.size());

  if (dataset.columns.size() != 1) {
    throw std::runtime_error("Invalid dataset format");
  }
  if (dataset.columns[0] != "id") {
    throw std::runtime_error("Invalid dataset format");
  }

  for (const auto& row : dataset.data) {
    graphs.emplace_back(std::stoull(row[0]));
  }
  return graphs;
}

template<uint32_t V>
auto load_none_isomorphic_undirected_graphs_of_up_to_size_n() -> std::vector<UGraph<V>>
{
  return load_graph_list<V>(std::format("none_isomorphic_undirected_graphs_of_up_to_size_{}.csv", V));
}

template<uint32_t V>
auto load_none_isomorphic_connected_undirected_graphs_of_up_to_size_n() -> std::vector<UGraph<V>>
{
  return load_graph_list<V>(std::format("none_isomorphic_connected_undirected_graphs_of_up_to_size_{}.csv", V));
}

}  // namespace wind::gm
