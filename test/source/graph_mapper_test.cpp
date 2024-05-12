

#include <string>

#include "graph_mapper/graph_mapper.hpp"

#include <doctest/doctest.h>

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
