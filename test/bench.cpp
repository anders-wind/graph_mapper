#include <random>

#include <benchmark/benchmark.h>

static void ColumnFirst(benchmark::State& state)
{
  auto rows = static_cast<size_t>(state.range(0));
  auto cols = 32ULL;
  auto matrix = std::vector<std::vector<float>>(rows, std::vector<float>(cols));
  for (auto row = 0ULL; row < rows; row++) {
    for (auto col = 0ULL; col < cols; col++) {
      matrix.at(row).at(col) = static_cast<float>(std::rand()) / 1000.0f;
    }
  }

  for (auto _ : state) {
    auto res = 0.0f;
    for (auto col = 0ULL; col < cols; col++) {
      for (auto row = 0ULL; row < rows; row++) {
        res += matrix.at(row).at(col);
      }
    }
    benchmark::DoNotOptimize(res);
  }
}

static void RowFirst(benchmark::State& state)
{
  auto rows = static_cast<size_t>(state.range(0));
  auto cols = 32ULL;
  auto matrix = std::vector<std::vector<float>>(rows, std::vector<float>(cols));
  for (auto row = 0ULL; row < rows; row++) {
    for (auto col = 0ULL; col < cols; col++) {
      matrix.at(row).at(col) = static_cast<float>(std::rand()) / 1000.0f;
    }
  }

  for (auto _ : state) {
    auto res = 0.0f;
    for (auto row = 0ULL; row < rows; row++) {
      for (auto col = 0ULL; col < cols; col++) {
        res += matrix.at(row).at(col);
      }
    }
    benchmark::DoNotOptimize(res);
  }
}

// L1 test
BENCHMARK(ColumnFirst)->DenseRange(64, 1024, 64)->Unit(benchmark::kMicrosecond);
BENCHMARK(RowFirst)->DenseRange(64, 1024, 64)->Unit(benchmark::kMicrosecond);

// L2 test
BENCHMARK(ColumnFirst)->DenseRange(64 * 16, 1024 * 8, 64 * 16)->Unit(benchmark::kMillisecond);
BENCHMARK(RowFirst)->DenseRange(64 * 16, 1024 * 8, 64 * 16)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
