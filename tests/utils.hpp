#pragma once

#include <filesystem>

namespace row_fileutils::tests {

class workspace
{
public:
  workspace(const std::filesystem::path& path);
  ~workspace();

private:
  const std::filesystem::path m_path;
};

}
