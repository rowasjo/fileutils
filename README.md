# fileutils

fileutils has utility functions to read, write, and sync files. E.g.:

```
atomic_write(
  "/tmp/myfile.txt",
  "/tmp/myfile.txt.tmp",
  std::string_view{"Hello, world!"});
```

## Build Guide

This project requires Catch2 for building and running tests. To disable building of tests, pass the CMake arg '-DBUILD_TESTING:BOOL=FALSE'.

Catch2 may be preinstalled, installed using a package manager, or built from source using the provided SuperBuild. SuperBuild is enabled by default. To disable SuperBuild, pass the CMake arg '-DUSE_SUPERBUILD:BOOL=FALSE'.

This particular style of SuperBuild:
  1. Fetches and builds dependencies (i.e. Catch2).
  2. Reruns configure and build on itself with '-DUSE_SUPERBUILD:BOOL=FALSE'.

You can build and install this project without tests and SuperBuild as follows:
```
cd <build-dir>
cmake
  -DBUILD_TESTING:BOOL=FALSE
  -DUSE_SUPERBUILD:BOOL=FALSE
  -DCMAKE_INSTALL_PREFIX=<install-prefix>
  <source-dir>
cmake --build . --target all
cmake --build . --target install
```
