cmake_minimum_required(VERSION 3.21)

project(graph_mapperTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

# ---- Dependencies ----

if (PROJECT_IS_TOP_LEVEL)
    find_package(graph_mapper REQUIRED)
    enable_testing()
endif ()

find_package(doctest CONFIG REQUIRED)

# ---- Tests ----

add_executable(
    graph_mapper_test
    source/graph_mapper_test.cpp
    source/graphs/graph_base_tests.cpp
    source/graphs/undirected_graph_tests.cpp
    source/main.cpp
    source/solvers/isomorphism_runner.cpp
    source/solvers/isomorphism_tests.cpp
    source/solvers/minimum_vertex_cover_tests.cpp
)

target_link_libraries(graph_mapper_test PRIVATE graph_mapper::graph_mapper doctest::doctest)
target_compile_features(graph_mapper_test PRIVATE cxx_std_23)
target_compile_definitions(graph_mapper_test PRIVATE GM_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/../data")
add_test(NAME graph_mapper_test COMMAND graph_mapper_test)

# ---- End-of-file commands ----

add_folders(Test)
