# Dependency SuperBuild

This particular style of SuperBuild:
  1. Fetches and builds dependencies (i.e. Catch2).
  2. Exports a 'superbuild-paths.cmake' which exports build information about the superbuild
  3. The main project consumes this build information using '-DCMAKE_PROJECT_<\project>_INCLUDE=<\superbuild-paths>'.

## Example - Build Single Configuration

Example to build dependencies and the main project with Release configuration.

```
mkdir -p <dir>/build-fileutils-superbuild-release <dir>/build-fileutils-release
cd <dir>/build-fileutils-superbuild-release
cmake -DCMAKE_BUILD_TYPE=Release <src-dir>/deps-superbuild
cmake --build . --target all

cd <dir>/build-fileutils-release
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_PROJECT_ROW_fileutils_INCLUDE=<dir>/build-fileutils-superbuild-release/superbuild-paths.cmake <src-dir>
cmake --build . --target all
```

## Example - Build Multiple Configurations

Configuration for building dependencies is independent of configuration for building the main project. For instance, we may want to do the following:
1. build dependencies with Release and RelWithDebInfo configurations.
2. build main project with Release, RelWithDebInfo, and Debug. Release uses release dependencies, whereas the other two uses RelWithDebInfo dependencies.

```
mkdir -p \
    <dir>/build-fileutils-superbuild-release \
    <dir>/build-fileutils-superbuild-relwithdebinfo \
    <dir>/build-fileutils-release \
    <dir>/build-fileutils-relwithdebinfo \
    <dir>/build-fileutils-debug

cd <dir>/build-fileutils-superbuild-release
cmake -DCMAKE_BUILD_TYPE=Release <src-dir>/deps-superbuild
cmake --build . --target all

cd <dir>/build-fileutils-superbuild-relwithdebinfo
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo <src-dir>/deps-superbuild
cmake --build . --target all

cd <dir>/build-fileutils-release
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_PROJECT_ROW_FileUtils_INCLUDE=<dir>/build-fileutils-superbuild-release/superbuild-paths.cmake <src-dir>
cmake --build . --target all

cd <dir>/build-fileutils-relwithdebinfo
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_PROJECT_ROW_FileUtils_INCLUDE=<dir>/build-fileutils-superbuild-relwithdebinfo/superbuild-paths.cmake <src-dir>
cmake --build . --target all

cd <dir>/build-fileutils-debug
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PROJECT_ROW_FileUtils_INCLUDE=<dir>/build-fileutils-superbuild-debug/superbuild-paths.cmake <src-dir>
cmake --build . --target all
```