# E2D

[![codecov](https://codecov.io/gh/emilhornlund/E2D/branch/master/graph/badge.svg?token=TGI4YZHLMA)](https://codecov.io/gh/emilhornlund/E2D)
[![Build Status](https://travis-ci.com/emilhornlund/E2D.svg?token=pxUUDgs4RTyjhHhLkJQm&branch=master)](https://travis-ci.com/emilhornlund/E2D)

My ambition is to write a simple 2D game engine in my spare time using only C++11 and SDL2.

## Prerequisites

- CMake (3.16+)
- C++11 compatible compiler (Clang/g++)
- SDL2
- Doxygen and Graphvis (Optional `-DE2D_BUILD_DOCS=ON`)

### Linux (Debian)

```
$ sudo apt install cmake g++ libsdl2-dev doxygen graphviz
```

### MacOS (Homebrew)

```
$ xcode-select —install
$ brew install cmake sdl2 doxygen graphviz
```

## Building from Source

### Linux and MacOS

```
$ git clone https://github.com/emilhornlund/E2D.git
$ mkdir E2D/build && cd E2D/build
$ cmake -D<OPTION>=<ON/OFF> ..
$ cmake --build .
```

By not specifying a build type, RelWithDebInfo will be chosen automatically.

#### Options


```
BUILD_SHARED_LIBS    "Build E2D as shared libraries. (default: ON)"
E2D_BUILD_EXAMPLES   "Build the E2D examples. (default: OFF)"
E2D_BUILD_DOCS       "Build the E2D API documentation. (default OFF)"
E2D_BUILD_TESTS      "Build the E2D tests. (default: OFF)"
E2D_BUILD_FRAMEWORKS "Build E2D as framework libraries on MacOS and release builds. (default: OFF)"
```

##### Extra
```
E2D_ENABLE_IPO      "Enable Interprocedural Optimization, aka Link Time Optimization (LTO). (default: OFF)"
E2D_ENABLE_COVERAGE "Enable coverage reporting for gcc/clang. (default OFF)"
```

#### Run the tests

Make sure to build the library with `-DE2D_BUILD_TESTS=ON` in order to compile the test executable and then run with `$ ctest`.

### Windows
    
Not currently supported but probably soon.
