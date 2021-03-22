include(ExternalProject)

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
  GIT_TAG v2.13.4
  CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
    -DBUILD_TESTING=OFF
    "-DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}")

ExternalProject_Get_Property(Catch2 INSTALL_DIR)
list(APPEND EXTRA_CMAKE_ARGS "-DCatch2_ROOT=${INSTALL_DIR}")

##
## ROW_FileUtils
##
ExternalProject_Add(ROW_FileUtils
  DEPENDS Catch2
  SOURCE_DIR ${PROJECT_SOURCE_DIR}
  CMAKE_ARGS ${EXTRA_CMAKE_ARGS} -DUSE_SUPERBUILD:BOOL=FALSE
  BUILD_ALWAYS TRUE
  INSTALL_COMMAND ""
  TEST_COMMAND ""
  BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
