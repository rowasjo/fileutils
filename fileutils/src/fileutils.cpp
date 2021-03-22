#include <row/fileutils.hpp>

#include <ios>
#include <streambuf>

#ifdef __unix__
  #include <unistd.h>
#endif

namespace row_fileutils {

std::string read_as_string(const std::filesystem::path& file) {
  std::ifstream t{file};

  if (!t)
    throw std::runtime_error{std::string{"Could not read file ["} + file.string() + "]"};

  std::string str;

  t.seekg(0, std::ios::end);
  str.reserve(t.tellg());
  t.seekg(0, std::ios::beg);

  str.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

  return str;
}


std::wstring read_as_wstring(const std::filesystem::path& file) {
  std::wifstream t{file};

  if (!t)
    throw std::runtime_error{std::string{"Could not read file ["} + file.string() + "]"};

  std::wstring str;

  t.seekg(0, std::ios::end);
  str.reserve(t.tellg());
  t.seekg(0, std::ios::beg);

  str.assign((std::istreambuf_iterator<wchar_t>(t)), std::istreambuf_iterator<wchar_t>());

  return str;
}


void sync_file(const std::filesystem::path& file) {
#ifdef __unix__
  FILE* fd = fopen(file.string().c_str(), "r");
  if (!fd) {
    std::string msg = "Got empty file descriptor when attempting to sync file path [" + file.string() + "]";
    throw std::runtime_error{msg};
  }

  fsync(fd->_fileno);
  fclose(fd);
#else
  static_assert(false, "sync_file is not supported on this platform");
#endif
}

}
