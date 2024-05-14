cmake_minimum_required(VERSION 3.21)

include(cmake/prelude.cmake)

project(
    graph_mapper
    VERSION 0.1.0
    DESCRIPTION "Short description"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(graph_mapper_graph_mapper source/graph_mapper.cpp)
add_library(graph_mapper::graph_mapper ALIAS graph_mapper_graph_mapper)

include(GenerateExportHeader)
generate_export_header(
    graph_mapper_graph_mapper
    BASE_NAME graph_mapper
    EXPORT_FILE_NAME export/graph_mapper/graph_mapper_export.hpp
    CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

if (NOT BUILD_SHARED_LIBS)
    target_compile_definitions(graph_mapper_graph_mapper PUBLIC GRAPH_MAPPER_STATIC_DEFINE)
endif ()

set_target_properties(
    graph_mapper_graph_mapper
    PROPERTIES CXX_VISIBILITY_PRESET hidden
               VISIBILITY_INLINES_HIDDEN YES
               VERSION "${PROJECT_VERSION}"
               SOVERSION "${PROJECT_VERSION_MAJOR}"
               EXPORT_NAME graph_mapper
               OUTPUT_NAME graph_mapper
)

target_include_directories(graph_mapper_graph_mapper ${warning_guard} PUBLIC "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>")

target_include_directories(graph_mapper_graph_mapper SYSTEM PUBLIC "\$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>")

target_compile_features(graph_mapper_graph_mapper PUBLIC cxx_std_20)

find_package(fmt REQUIRED)
target_link_libraries(graph_mapper_graph_mapper PRIVATE fmt::fmt)

# ---- Install rules ----

if (NOT CMAKE_SKIP_INSTALL_RULES)
    include(cmake/install-rules.cmake)
endif ()

# ---- Developer mode ----

if (NOT graph_mapper_DEVELOPER_MODE)
    return()
elseif (NOT PROJECT_IS_TOP_LEVEL)
    message(AUTHOR_WARNING "Developer mode is intended for developers of graph_mapper")
endif ()

include(cmake/dev-mode.cmake)
