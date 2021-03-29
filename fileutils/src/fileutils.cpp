#include <row/fileutils.hpp>

#ifdef __unix__
  #include <unistd.h>
#endif

namespace row_fileutils {

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
