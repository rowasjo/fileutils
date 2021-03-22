#pragma once

#include <filesystem>
#include <fstream>
#include <string_view>
#include <string>

namespace row_fileutils {

std::string read_as_string(const std::filesystem::path& file);

std::wstring read_as_wstring(const std::filesystem::path& file);

template<class CharT, class Traits = std::char_traits<CharT>>
void write(const std::filesystem::path& file, std::basic_string_view<CharT, Traits> contents);

template<class CharT, class Traits = std::char_traits<CharT>>
void atomic_write(
  const std::filesystem::path& file,
  const std::filesystem::path& tmp_file,
  std::basic_string_view<CharT, Traits> contents);

void sync_file(const std::filesystem::path& file);

//
// Template Definitions
//

template<class CharT, class Traits>
void write(const std::filesystem::path& file, std::basic_string_view<CharT, Traits> contents) {

  std::basic_ofstream<CharT, Traits> stream{file};
  if (!stream.good()) {
    std::filesystem::remove(file);
    std::string msg = "Failed to open file [" + file.string() + "]";
    throw std::runtime_error{msg};
  }

  stream << contents;
  stream.close();

  if (!stream.good()) {
    std::string msg = "Writing to file [" + file.string() + "] failed";
    throw std::runtime_error{msg};
  }
}


template<class CharT, class Traits>
void atomic_write(
  const std::filesystem::path& file,
  const std::filesystem::path& tmp_file,
  std::basic_string_view<CharT, Traits> contents) {

  write(tmp_file, contents);
  sync_file(tmp_file);
  std::filesystem::rename(tmp_file, file);
}

}
