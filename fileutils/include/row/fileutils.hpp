#pragma once

#include <row/row_fileutils_export.h>

#include <filesystem>
#include <fstream>
#include <ios>
#include <string_view>
#include <string>
#include <streambuf>

namespace row_fileutils {

/*!
 * \brief Read file contents to string
 */
template<class CharT, class Traits = std::char_traits<CharT>>
std::basic_string<CharT, Traits> read_as_basic_string(const std::filesystem::path& file);

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
void ROW_FILEUTILS_EXPORT sync_file(const std::filesystem::path& file);

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
std::basic_string<CharT, Traits> ROW_FILEUTILS_EXPORT read_as_basic_string(const std::filesystem::path& file) {
  std::basic_ifstream<CharT> fs{file};

  if (!fs)
    throw std::runtime_error{std::string{"Could not read file ["} + file.string() + "]"};

  std::basic_string<CharT, Traits> str;

  fs.seekg(0, std::ios::end);
  str.reserve(fs.tellg());
  fs.seekg(0, std::ios::beg);

  str.assign((std::istreambuf_iterator<CharT>(fs)), std::istreambuf_iterator<CharT>());

  return str;
}


inline std::string read_as_string(const std::filesystem::path& file) {
  return read_as_basic_string<std::string::value_type>(file);
}


inline std::wstring read_as_wstring(const std::filesystem::path& file) {
  return read_as_basic_string<std::wstring::value_type>(file);
}


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
