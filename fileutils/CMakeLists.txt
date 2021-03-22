
add_library(row_fileutils
  src/fileutils.cpp
  include/row/fileutils.hpp)

target_include_directories(row_fileutils PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
  $<INSTALL_INTERFACE:include>)

install(TARGETS row_fileutils EXPORT row_fileutilsTargets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT row_fileutils_Runtime
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT row_fileutils_Runtime
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT row_fileutils_Development
  INCLUDES DESTINATION include)

install(
  DIRECTORY include/
  DESTINATION include
  COMPONENT row_fileutils_Development)
