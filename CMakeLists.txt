
cmake_minimum_required(VERSION 3.12)

include(CMakePrintHelpers)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

##
## SuperBuild (optional).
##

option(USE_SUPERBUILD "" TRUE)

if(USE_SUPERBUILD)
  project(ROW_FileUtils.superbuild VERSION 1.0.0)
  message(STATUS "Configuring project ${CMAKE_PROJECT_NAME} ...")
  include(ROW_FileUtils/superbuild)
  return()
endif()

##
## ROW_FileUtils project
##

project(ROW_FileUtils VERSION 1.0.0)
message(STATUS "Configuring project ${CMAKE_PROJECT_NAME} ...")
enable_testing()

add_subdirectory(fileutils)

include(CTest)
if(BUILD_TESTING)
  message(STATUS "Configuring ${CMAKE_PROJECT_NAME} tests ...")
  find_package(Catch2 REQUIRED)
  include(Catch)
  add_subdirectory(tests)
endif()

add_subdirectory(exports)

# Only include packaging if we are the top level project
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  include(ROW_FileUtils/packaging)
endif()
