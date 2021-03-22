#include "utils.hpp"

namespace row_fileutils::tests {

namespace {

void remove_contents(const std::filesystem::path& path) {
  for (const auto& entry : std::filesystem::directory_iterator(path))
    std::filesystem::remove_all(entry.path());
}

}

workspace::workspace(const std::filesystem::path& path) : m_path{path} {
  std::filesystem::create_directories(path);
  remove_contents(path);
}

workspace::~workspace() {
  remove_contents(m_path);
}

}
