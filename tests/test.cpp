#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "utils.hpp"
#include <row/fileutils.hpp>

using namespace row_fileutils::tests;
using namespace row_fileutils;

namespace {

std::filesystem::path workspace_dir() {
  std::filesystem::path dir = std::filesystem::temp_directory_path();
  dir /= "fileutils";
  return dir;
}
}

TEST_CASE("Read non-existent file throws", "[fileutils]") {
  workspace w{workspace_dir()};

  std::filesystem::path nonexistent_file = workspace_dir() /= "nonexistent-file.txt";
  REQUIRE_THROWS_WITH(read_as_string(nonexistent_file), Catch::Contains(nonexistent_file));
}

TEST_CASE("Write and read empty file", "[fileutils]") {
  workspace w{workspace_dir()};

  std::filesystem::path empty_file = workspace_dir() /= "empty-file.txt";
  write(empty_file, std::string_view{""});

  CHECK(read_as_string(empty_file) == "");
}

TEST_CASE("Atomically write then read file", "[fileutils]") {
  workspace w{workspace_dir()};

  const std::filesystem::path file = workspace_dir() /= "test-file.txt";
  constexpr char contents[] = "my file is filled with chars";

  atomic_write(file, std::filesystem::path{file} += ".tmp", std::string_view{contents});
  CHECK(read_as_string(file) == contents);
}

TEST_CASE("Atomically write then read file using wchar_t", "[fileutils]") {
  workspace w{workspace_dir()};

  const std::filesystem::path file = workspace_dir() /= "test-file.txt";
  constexpr wchar_t contents[] = L"my file is filled with chars";

  atomic_write(file, std::filesystem::path{file} += ".tmp", std::wstring_view{contents});
  CHECK(read_as_wstring(file) == contents);
}

TEST_CASE("Atomically overwrite file", "[fileutils]") {
  workspace w{workspace_dir()};

  const std::filesystem::path file = workspace_dir() /= "test-file.txt";

  constexpr char contents1[] = "my file is filled with chars";
  constexpr char contents2[] = "my file is overwritten with new chars";

  atomic_write(file, std::filesystem::path{file} += ".tmp1", std::string_view{contents1});
  atomic_write(file, std::filesystem::path{file} += ".tmp2", std::string_view{contents2});

  CHECK(read_as_string(file) == contents2);
}

TEST_CASE("write to invalid filepath throws runtime_error", "[fileutils]") {
  const std::filesystem::path invalid_path;
  CHECK_THROWS_AS(write(invalid_path, std::string_view{""}), std::runtime_error);
}

TEST_CASE("write to existing directory throws runtime_error", "[fileutils]") {
  workspace w{workspace_dir()};

  std::filesystem::path test_dir = workspace_dir() /= "testdir";
  std::filesystem::create_directory(test_dir);

  CHECK_THROWS_AS(write(test_dir, std::string_view{""}), std::runtime_error);
}

TEST_CASE("write to symbolic link overwrites original", "[fileutils]") {
  workspace w{workspace_dir()};

  std::filesystem::path original = workspace_dir() /= "file.orig";
  std::filesystem::path link = workspace_dir() /= "file.link";

  constexpr char contents1[] = "my file is filled with chars";
  constexpr char contents2[] = "my file is overwritten with new chars";

  write(original, std::string_view{contents1});
  std::filesystem::create_symlink(original, link);

  write(link, std::string_view{contents2});

  CHECK(read_as_string(original) == contents2);
}
