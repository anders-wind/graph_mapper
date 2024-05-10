if(PROJECT_IS_TOP_LEVEL)
  set(CMAKE_INSTALL_INCLUDEDIR
      "include/graph_mapper-${PROJECT_VERSION}"
      CACHE STRING "")
  set_property(CACHE CMAKE_INSTALL_INCLUDEDIR PROPERTY TYPE PATH)
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package graph_mapper)

install(
  DIRECTORY include/ "${PROJECT_BINARY_DIR}/export/"
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
  COMPONENT graph_mapper_Development)

install(
  TARGETS graph_mapper_graph_mapper
  EXPORT graph_mapperTargets
  RUNTIME #
          COMPONENT graph_mapper_Runtime
  LIBRARY #
          COMPONENT graph_mapper_Runtime
          NAMELINK_COMPONENT graph_mapper_Development
  ARCHIVE #
          COMPONENT graph_mapper_Development
  INCLUDES #
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

write_basic_package_version_file("${package}ConfigVersion.cmake"
                                 COMPATIBILITY SameMajorVersion)

# Allow package maintainers to freely override the path for the configs
set(graph_mapper_INSTALL_CMAKEDIR
    "${CMAKE_INSTALL_LIBDIR}/cmake/${package}"
    CACHE STRING "CMake package config location relative to the install prefix")
set_property(CACHE graph_mapper_INSTALL_CMAKEDIR PROPERTY TYPE PATH)
mark_as_advanced(graph_mapper_INSTALL_CMAKEDIR)

install(
  FILES cmake/install-config.cmake
  DESTINATION "${graph_mapper_INSTALL_CMAKEDIR}"
  RENAME "${package}Config.cmake"
  COMPONENT graph_mapper_Development)

install(
  FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
  DESTINATION "${graph_mapper_INSTALL_CMAKEDIR}"
  COMPONENT graph_mapper_Development)

install(
  EXPORT graph_mapperTargets
  NAMESPACE graph_mapper::
  DESTINATION "${graph_mapper_INSTALL_CMAKEDIR}"
  COMPONENT graph_mapper_Development)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
