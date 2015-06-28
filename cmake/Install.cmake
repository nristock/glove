include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/glove/GloveVersion.cmake"
  VERSION ${BD_VERSION}
  COMPATIBILITY SameMajorVersion
)

export(EXPORT GloveTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/glove/GloveTargets.cmake"
  NAMESPACE Glove::
)

configure_package_config_file(
    "${PROJECT_ROOT}/cmake/GloveConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/glove/GloveConfig.cmake"
    INSTALL_DESTINATION ${CONFIG_PACKAGE_DIR}
    PATH_VARS INCLUDE_INSTALL_DIR LIB_INSTALL_DIR MODULE_INSTALL_DIR
)

install(EXPORT GloveTargets
  FILE
    GloveTargets.cmake
  NAMESPACE
    Glove::
  DESTINATION
    ${CONFIG_PACKAGE_DIR}
)
install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/glove/GloveConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/glove/GloveVersion.cmake"
  DESTINATION
    ${CONFIG_PACKAGE_DIR}
)