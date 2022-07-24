##
## SuperBuild for building dependencies (optional).
##

cmake_minimum_required(VERSION 3.12)
include(CMakePrintHelpers)

project(ROW_FileUtils.superbuild VERSION 1.0.0)

include(ExternalProject)

# Use Release configuration for dependencies by default
#
# TODO: support mulit-configuration generators.
#       CMAKE_BUILD_TYPE only works for single-configuration generators.
set(CMAKE_BUILD_TYPE Release CACHE STRING "")

##
## Catch 2
##
## NOTE: By pulling from GitHub the project is always considered out-of-date.
##       See: https://gitlab.kitware.com/cmake/cmake/-/issues/19703
##
ExternalProject_Add(Catch2
  PREFIX Catch2-prefix
  INSTALL_DIR Catch2-prefix/install_dir
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v2.13.9
  CMAKE_ARGS
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
    -DBUILD_TESTING=OFF
    "-DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}")

ExternalProject_Get_Property(Catch2 INSTALL_DIR)
set(Catch2_INSTALL_DIR ${INSTALL_DIR})

##
## Export install paths
##
configure_file(superbuild-paths.cmake.in superbuild-paths.cmake @ONLY)
