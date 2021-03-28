
add_library(row_fileutils
  src/fileutils.cpp
  include/row/fileutils.hpp)

target_include_directories(row_fileutils PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
  $<INSTALL_INTERFACE:include>)

set_target_properties(
  row_fileutils PROPERTIES
  SOVERSION ${PROJECT_VERSION_MAJOR}
  VERSION ${PROJECT_VERSION}
  EXPORT_NAME fileutils)

add_library(row_fileutils::fileutils ALIAS row_fileutils)

include(GenerateExportHeader)
generate_export_header(row_fileutils EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/include/row/row_fileutils_export.h)

install(TARGETS row_fileutils EXPORT row_fileutilsTargets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
          COMPONENT row_fileutils_Runtime
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
          COMPONENT row_fileutils_Runtime
          NAMELINK_COMPONENT row_fileutils_Development
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
          COMPONENT row_fileutils_Development
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(
  DIRECTORY include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  COMPONENT row_fileutils_Development)

install(
  DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  COMPONENT row_fileutils_Development)
