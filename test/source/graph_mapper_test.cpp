

#include <string>

#include <doctest/doctest.h>

#include "graph_mapper/graph_mapper.hpp"

namespace wind::gm
{

TEST_SUITE("library")
{
  TEST_CASE("Name is graph_mapper")
  {
    auto const exported = exported_class {};
    REQUIRE(std::string("graph_mapper") == exported.name());
  }
}

}  // namespace wind::gm
