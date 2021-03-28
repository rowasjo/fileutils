
set(ROW_FileUtils_INSTALL_CMAKEDIR
  ${CMAKE_INSTALL_LIBDIR}/cmake/row_fileutils
  CACHE STRING "")

cmake_print_variables(CMAKE_INSTALL_LIBDIR ROW_FileUtils_INSTALL_CMAKEDIR)

install(EXPORT row_fileutilsTargets
  FILE row_fileutilsTargets.cmake
  NAMESPACE row_fileutils::
  DESTINATION ${ROW_FileUtils_INSTALL_CMAKEDIR}
  COMPONENT row_fileutils_Development)

include(CMakePackageConfigHelpers)

configure_package_config_file(
  row_fileutilsConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/row_fileutilsConfig.cmake
  INSTALL_DESTINATION ${ROW_FileUtils_INSTALL_CMAKEDIR})

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/row_fileutilsConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/row_fileutilsConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/row_fileutilsConfigVersion.cmake
  DESTINATION ${ROW_FileUtils_INSTALL_CMAKEDIR}
  COMPONENT row_fileutils_Development)
