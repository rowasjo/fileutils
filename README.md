# fileutils

fileutils has utility functions to read, write, and sync files.

## Use Cases

Write file:
```
write("/tmp/myfile.txt", std::string_view{"Hello, world!"});
```

Sync file to storage:
```
sync("/tmp/myfile.txt");
```

Read file:
```
std::string contents = read_as_string("/tmp/myfile.txt");
```

Atomically write file:
```
atomic_write(
  "/tmp/myfile.txt",
  "/tmp/myfile.txt.tmp",
  std::string_view{"Hello, world!"});
```

## Build Guide

This project requires Catch2 for building and running tests. To disable building of tests, pass the CMake arg '-DBUILD_TESTING:BOOL=FALSE'.

Catch2 may be preinstalled, installed using a package manager, or built from source using the provided dependency SuperBuild. See [deps-superbuild](deps-superbuild/README.md) for details.
