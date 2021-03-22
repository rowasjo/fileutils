
install(EXPORT row_fileutilsTargets
  FILE row_fileutilsTargets.cmake
  NAMESPACE row_fileutils::
  DESTINATION lib/cmake/row_fileutils
  COMPONENT row_fileutils_Development)

include(CMakePackageConfigHelpers)

configure_package_config_file(
  row_fileutilsConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/row_fileutilsConfig.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/row_fileutils)

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/row_fileutilsConfigVersion.cmake
  COMPATIBILITY SameMajorVersion)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/row_fileutilsConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/row_fileutilsConfigVersion.cmake
  DESTINATION lib/cmake/row_fileutils
  COMPONENT row_fileutils_Development)
