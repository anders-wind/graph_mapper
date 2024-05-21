#pragma once
#include <filesystem>

namespace wind::gm
{

#if defined(GM_DATA_DIR)
static const auto dataset_dir = std::filesystem::path {GM_DATA_DIR};
#endif

}  // namespace wind::gm