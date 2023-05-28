![example workflow](https://github.com/emilhornlund/E2D/actions/workflows/main.yml/badge.svg)

# E2D

My own, Emil's 2D (E2D) game engine written in C++20 using SDL2.

## Prerequisites

Before building and running the E2D project, ensure you have the following prerequisites:

- Operating System: E2D is supported on Linux, Windows, and macOS.
- C++20 compiler: E2D requires a compiler that supports the C++20 standard. Currently, GNU C++ (GCC), Clang, MinGW, and MSVC (Microsoft Visual C++) are supported.
- CMake 3.22 or higher: E2D uses CMake as the build system. Make sure you have CMake version 3.22 or higher installed on your system. You can download CMake from the [official CMake website](https://cmake.org/download/).
- SDL2 library: E2D uses the SDL2 library for graphics and input handling. Make sure you have SDL2 installed on your Linux system. For Windows and macOS, E2D already comes bundled with all the required external libraries, including SDL2. You don't need to install it separately. You can find installation instructions for SDL2 in the [official SDL2 documentation](https://www.libsdl.org/download-2.0.php).

## Configuration

The E2D project provides several configuration options that can be set during the build process. These options are controlled via CMake variables. The following configuration options are available:

- `CMAKE_BUILD_TYPE`: Choose the type of build. Valid options are `Debug` or `Release`. By default, the build type is set to `Release`.
- `BUILD_SHARED_LIBS`: Set this variable to `ON` to build E2D as shared libraries or `OFF` to build it as static libraries. The default value is `ON`, which means E2D will be built as shared libraries.
- `E2D_BUILD_ENGINE`: Set this variable to `ON` to enable the building of the E2D library module called "Engine", or `OFF` to disable it. By default, building the "Engine" module is enabled.
- `E2D_BUILD_EXAMPLES`: Set this variable to `ON` to enable the building of the project examples, or `OFF` to disable it. By default, building the examples is disabled.
- `E2D_BUILD_FRAMEWORKS`: Set this variable to `ON` to build E2D as framework libraries (release only), or `OFF` to build according to `BUILD_SHARED_LIBS`. By default, framework library building is disabled.
- `E2D_GENERATE_PDB`: Set this variable to `ON` to generate PDB debug symbols for MSVC compiler, or `OFF` to disable PDB generation. PDB files contain debugging information and are specific to Windows and MSVC compilers. By default, PDB generation is enabled.
- `E2D_USE_STATIC_STD_LIBS`:  Set this variable to  `ON` to statically link to the standard libraries, or `OFF` to use them as DLLs. By default, statically linking the standard libraries are disabled.
- `E2D_USE_SYSTEM_DEPS`: Set this variable to `ON` to use system-installed external dependencies, or `OFF` to use the bundled dependencies. By default, the bundled dependencies are used. 

To configure these options, use the `-D` flag when generating the build files. For example:

```shell
cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON ..
```

## Installation

To build and run the E2D project, follow these steps:

1. Clone the repository:
    ```shell
    git clone git@github.com:emilhornlund/E2D.git
    ```

2. Generate the build files using CMake:
    ```shell
    cmake -S . -B build
    ```

3. Build and install the project:
    ```shell
    cmake --build build --target install --config Release
    ```

## Example

To demonstrate the usage of the E2D library, we provide a simple example below:

### CMakeLists.txt

In your CMakeLists.txt file, include the following lines to set up the E2D library and create an executable for your game:

```cmake
cmake_minimum_required(VERSION 3.12)

project(MyGame)

find_package(E2D COMPONENTS Engine REQUIRED)

add_executable(mygame main.cpp)
target_link_libraries(mygame PRIVATE E2D::Engine)
```

Make sure to adjust the project name, target name, and source file names according to your project structure.

### main.cpp

Create a main.cpp file with the following code, which sets up your game class derived from `e2d::Application`:

```cpp
#include <E2D/Engine/Application.hpp>

class MyGame final : public e2d::Application {
public:
    MyGame();

    ~MyGame() final;
};

MyGame::MyGame() : e2d::Application("MyGame") {}

MyGame::~MyGame() = default;

int main() {
    auto *application = new MyGame();

    int exitCode = application->run();

    delete application;
    application = nullptr;

    return exitCode;
}
```

Ensure that you update the class name and the `Application` constructor parameter according to your desired game title.

This example demonstrates the basic setup of an E2D game using the `e2d::Application` class. You can build and run the `mygame` executable to see your game in action.

For more comprehensive examples showcasing various features and functionalities of the E2D library, you can explore the "examples" directory at the root of the repository. The examples directory contains additional sample projects and code snippets that illustrate different aspects of game development using E2D.

For more detailed information on how to use the E2D library and its various features, please refer to the documentation and additional examples provided in the project repository.

## License

This project is licensed under the MIT License. See the [LICENSE](https://raw.githubusercontent.com/emilhornlund/E2D/main/LICENSE) file for more details.
