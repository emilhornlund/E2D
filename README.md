![example workflow](https://github.com/emilhornlund/E2D/actions/workflows/main.yml/badge.svg)

# E2D

E2D is a modern 2D game engine written in C++20 that leverages the SDL2 library. Currently a work in progress, the project aims to provide developers with a powerful and flexible platform to create cross-platform 2D games with ease. With its comprehensive features, intuitive API, and extensive documentation, E2D aims to empower developers to bring their game ideas to life efficiently and deliver captivating gaming experiences.

## Prerequisites

Before building and running the E2D project, ensure you have the following prerequisites:

- **Operating System:** E2D is supported on Linux, Windows, and macOS.
- **C++20 Compiler:** E2D requires a compiler that supports the C++20 standard. Supported compilers include GNU C++ (GCC), Clang, MinGW, and MSVC (Microsoft Visual C++).
- **CMake 3.22 or higher:** E2D uses CMake as the build system. Ensure that you have CMake version 3.22 or higher installed on your system. You can download CMake from the [official CMake website](https://cmake.org/download/).
- **SDL2 Library:** E2D uses the SDL2 library for graphics and input handling. SDL2 is already bundled with E2D for Windows and macOS. For Linux, make sure you have SDL2 installed on your system. Installation instructions for SDL2 can be found in the [official SDL2 documentation](https://www.libsdl.org/download-2.0.php).

## Configuration

The E2D project provides several configuration options that can be set during the build process. These options are controlled via CMake variables. The following configuration options are available:

- `CMAKE_BUILD_TYPE`: Choose the type of build. Valid options are `Debug` or `Release`. The default build type is set to `Release`.
- `BUILD_SHARED_LIBS`: Set this variable to `ON` to build E2D as shared libraries or `OFF` to build it as static libraries. The default value is `ON`, which builds E2D as shared libraries.
- `E2D_BUILD_ENGINE`: Set this variable to `ON` to enable building the E2D library module called "Engine" or `OFF` to disable it. Building the "Engine" module is enabled by default.
- `E2D_BUILD_EXAMPLES`: Set this variable to `ON` to enable building the project examples or `OFF` to disable it. Building the examples is disabled by default.
- `E2D_BUILD_FRAMEWORKS`: Set this variable to `ON` to build E2D as framework libraries (release only), or `OFF` to build according to `BUILD_SHARED_LIBS`. Framework library building is disabled by default.
- `E2D_GENERATE_PDB`: Set this variable to `ON` to generate PDB debug symbols for the MSVC compiler or `OFF` to disable PDB generation. PDB files contain debugging information and are specific to Windows and MSVC compilers. PDB generation is enabled by default.
- `E2D_USE_STATIC_STD_LIBS`:  Set this variable to `ON` to statically link to the standard libraries or `OFF` to use them as DLLs. Statically linking the standard libraries is disabled by default.
- `E2D_USE_SYSTEM_DEPS`: Set this variable to `ON` to use system-installed external dependencies or `OFF` to use the bundled dependencies. The bundled dependencies are used by default.

To configure these options, use the `-D` flag when generating the build files. For example:

```shell
cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON ...
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

In your `CMakeLists.txt` file, include the following lines to set up the E2D library and create an executable for your game:

```cmake
cmake_minimum_required(VERSION 3.12)

project(MyGame)

find_package(E2D COMPONENTS Engine REQUIRED)

add_executable(mygame main.cpp)
target_link_libraries(mygame PRIVATE E2D::Engine)
```

Make sure to adjust the project name, target name, and source file names according to your project structure.

### main.cpp

Create a `main.cpp` file with the following code, which sets up your game class derived from `e2d::Application`:

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

## Collaboration

E2D welcomes collaboration and contributions from the developer community. If you are interested in contributing to the project, you can follow these steps to get started:

1. Fork the E2D repository on GitHub.
2. Make your desired changes or additions to the codebase.
3. Ensure that your changes align with the project's coding style and guidelines.
4. Test your changes thoroughly to ensure they do not introduce any regressions or issues.
5. Submit a pull request (PR) to the main E2D repository, outlining the changes you have made and providing a clear description of your contribution.
6. The project maintainers will review your PR, provide feedback, and work with you to refine the changes if necessary.
7. Once the changes have been reviewed and approved, they will be merged into the main repository.

When collaborating on E2D, it is important to adhere to the project's code of conduct and respect the ideas and opinions of other contributors. Open and constructive communication is encouraged to foster a positive and inclusive environment for all participants.

In addition to code contributions, you can also contribute to the project by reporting bugs, suggesting new features, or providing feedback on existing functionality. You can do this by opening issues on the GitHub repository, clearly describing the problem or suggestion and providing any relevant details.

By collaborating with the E2D community, you can help shape the future of the project and contribute to the growth and improvement of the 2D game development ecosystem.

Thank you for considering contributing to E2D! We look forward to your involvement in the project.

## License

This project is licensed under the MIT License, which is a permissive open-source license. The MIT License grants you the freedom to use, modify, and distribute this project, both in its original form and any modifications you make, subject to certain conditions.

The full text of the MIT License can be found in the [LICENSE](https://raw.githubusercontent.com/emilhornlund/E2D/main/LICENSE) file. It is important to review the license file for complete details, but in summary:

- You are free to use this project for personal or commercial purposes.
- You are allowed to modify the project and incorporate it into your own projects.
- You are permitted to distribute the project, either in its original form or as part of a larger work.
- You must include a copy of the original MIT License in any distribution of this project.
- The project is provided "as is," without any warranty or liability.

Please read the [LICENSE](https://raw.githubusercontent.com/emilhornlund/E2D/main/LICENSE) file for the complete terms and conditions of the MIT License.

If you have any questions about the licensing or usage of this project, please refer to the license file or contact the project author.
