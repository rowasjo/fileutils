
add_executable(row_fileutils_tests
  test.cpp
  utils.hpp
  utils.cpp)

target_link_libraries(row_fileutils_tests PRIVATE
  row_fileutils
  Catch2::Catch2)

catch_discover_tests(row_fileutils_tests)
