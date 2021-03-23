#pragma once

#include <filesystem>
#include <fstream>
#include <string_view>
#include <string>

namespace row_fileutils {

std::string read_as_string(const std::filesystem::path& file);

std::wstring read_as_wstring(const std::filesystem::path& file);

/*!
 * \brief Write to file
 */
template<class CharT, class Traits = std::char_traits<CharT>>
void write(const std::filesystem::path& file, std::basic_string_view<CharT, Traits> contents);

/*!
 * \brief Sync file to storage
 *
 * Implemented using POSIX fsync on Linux. Not yet supported on other platforms.
 */
void sync_file(const std::filesystem::path& file);

/*!
 * \brief Atomically write to file
 *
 * atomic_write (1) writes to temporary file, (2) ensures it is synced to storage,
 * and (3) renames temporary file to target file. The goal is to ensure that the
 * target file is either completely written or not affected at all.
 */
template<class CharT, class Traits = std::char_traits<CharT>>
void atomic_write(
  const std::filesystem::path& file,
  const std::filesystem::path& tmp_file,
  std::basic_string_view<CharT, Traits> contents);

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
