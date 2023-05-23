# E2D

My own, Emil's 2D (E2D) game engine written in C++20 using SDL2.

## Prerequisites

Before building and running the E2D project, ensure you have the following prerequisites:

- Operating System: E2D is supported on Linux, Windows, and macOS.
- C++20 compiler: E2D requires a compiler that supports the C++20 standard. Currently, GNU C++ (GCC), Clang, MinGW, and MSVC (Microsoft Visual C++) are supported.
- CMake 3.22 or higher: E2D uses CMake as the build system. Make sure you have CMake version 3.22 or higher installed on your system. You can download CMake from the [official CMake website](https://cmake.org/download/).
- SDL2 library: E2D uses the SDL2 library for graphics and input handling. Make sure you have SDL2 installed on your Linux system. For Windows and MacOS, E2D already comes bundled with all the required external libraries, including SDL2. You don't need to install it separately. You can find installation instructions for SDL2 in the [official SDL2 documentation](https://www.libsdl.org/download-2.0.php).

## Configuration

The E2D project provides several configuration options that can be set during the build process. These options are controlled via CMake variables. The following configuration options are available:

- `CMAKE_BUILD_TYPE`: Choose the type of build. Valid options are `Debug` or `Release`. By default, the build type is set to `Release`.
- `BUILD_SHARED_LIBS`: Set this variable to `TRUE` to build E2D as shared libraries or `FALSE` to build it as static libraries. The default value is `TRUE`, which means E2D will be built as shared libraries.

To configure these options, use the `-D` flag when generating the build files. For example:

```shell
cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=FALSE ..
```

## Installation

To build and run the E2D project, follow these steps:

1. Clone the repository:
    ```shell
    git clone git@github.com:emilhornlund/E2D.git
    ```

2. Create a build directory:
    ```shell
    mkdir build
    cd build
    ```

3. Generate the build files using CMake:
    ```shell
    cmake ..
    ```

4. Build the project:
    ```shell
    cmake --build . --target install --config Release
    ```

## License

This project is licensed under the MIT License. See the [LICENSE](https://raw.githubusercontent.com/emilhornlund/E2D/main/LICENSE) file for more details.