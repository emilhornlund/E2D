![example workflow](https://github.com/emilhornlund/E2D/actions/workflows/main.yml/badge.svg)

# E2D

- [Overview](#overview)
- [Prerequisites](#prerequisites)
    - [Instructions](#prerequisites-instructions)
        - [Windows](#windows-prerequisites)
        - [macOS](#macos-prerequisites)
        - [Linux](#linux-prerequisites)
- [Configuration](#configuration)
- [Installation](#installation)
- [Packaging](#packaging)
- [Example](#example)
- [Generating Documentation](#generating-documentation)
    - [Instructions for Installing Doxygen](#instructions-for-installing-doxygen)
        - [Windows](#windows-doxygen-installation)
        - [macOS](#macos-doxygen-installation)
        - [Linux](#linux-doxygen-installation)
- [Code Quality](#code-quality)
    - [Clang-Tidy](#clang-tidy)
    - [Clang-Format](#clang-format)
- [Collaboration](#collaboration)
- [License](#license)

## Overview

E2D is a modern 2D game engine written in C++20 that leverages the SDL2 library. Currently, a work in progress, the project aims to provide developers with a powerful and flexible platform to create cross-platform 2D games with ease. With its comprehensive features, intuitive API, and extensive documentation, E2D aims to empower developers to bring their game ideas to life efficiently and deliver captivating gaming experiences.

## Prerequisites

Before building and running the E2D project, ensure you have the following prerequisites:

- **Operating System:** E2D is supported on Linux, Windows, and macOS.
- **C++20 Compiler:** E2D requires a compiler that supports the C++20 standard. Supported compilers include GNU C++ (GCC), Clang, MinGW, ClangCL and MSVC (Microsoft Visual C++).
- **CMake 3.22 or higher:** E2D uses CMake as the build system. Ensure that you have CMake version 3.22 or higher installed on your system. You can download CMake from the [official CMake website](https://cmake.org/download/).
- **SDL2 Library:** E2D uses the SDL2 library for graphics and input handling. SDL2 is already bundled with E2D for Windows and macOS. For Linux, make sure you have SDL2 installed on your system. Installation instructions for SDL2 can be found in the [official SDL2 documentation](https://www.libsdl.org/download-2.0.php).
- **Doxygen (optional):** If you plan on generating the documentation, Doxygen is required. You can install Doxygen using the instructions provided for your specific operating system.

### Prerequisites Instructions

#### Windows Prerequisites

To set up the development environment on Windows, follow these steps:

1. **Compiler:** Install one of the following C++20 compilers:
   - **Visual Studio:** Download and install Visual Studio 2019 or newer from the [official Microsoft website](https://visualstudio.microsoft.com/downloads/). Make sure to select the C++ development workload during the installation process.
   - **MinGW-w64:** Download and install MinGW-w64 from the [official MinGW-w64 website](http://mingw-w64.org/doku.php). Make sure to select the C++ components during the installation process.

2. **CMake:** Download and install CMake version 3.22 or higher from the [official CMake website](https://cmake.org/download/). Make sure to add CMake to your system's PATH during the installation process.

3. **SDL2:** SDL2 is already bundled with E2D for Windows, so no additional installation is required.

4. **Ninja:** To enhance the build performance, it is recommended to use Ninja as the build system. Install Ninja by running the following command using Chocolatey:

   ```shell
   choco install ninja
   ```

   If you don't have Chocolatey installed, you can manually download Ninja from the [official Ninja website](https://ninja-build.org/) and add it to your system's PATH.

#### macOS Prerequisites

To set up the development environment on macOS, follow these steps:

1. **Compiler:** macOS comes with Clang installed by default, which supports C++20. No additional installation is required.

2. **CMake:** Install CMake version 3.22 or higher using Homebrew. Open a terminal and run the following command:

   ```shell
   brew install cmake
   ```

   Homebrew will download and install CMake on your system.

3. **SDL2:** SDL2 is already bundled with E2D for macOS, so no additional installation is required.

4. **Ninja:** To enhance the build performance, it is recommended to use Ninja as the build system. Install Ninja by running the following command using Homebrew:

   ```shell
   brew install ninja
   ```

   Homebrew will download and install Ninja on your system.

#### Linux Prerequisites

To set up the development environment on Linux, follow these steps:

1. **Compiler:** Install one of the following C++20 compilers:
   - **GCC (GNU Compiler Collection):** Open a terminal and run the following command to install GCC:

     ```shell
     sudo apt-get update
     sudo apt-get install build-essential
     ```

   - **Clang:** Open a terminal and run the following command to install Clang:

     ```shell
     sudo apt-get update
     sudo apt-get install clang
     ```

   Choose the compiler that suits your preference.

2. **CMake:** Install CMake version 3.22 or higher using the package manager for your Linux distribution. For example, on Ubuntu, open a terminal and run the following command:

   ```shell
   sudo apt-get update
   sudo apt-get install cmake
   ```

   Adjust the command based on the package manager used in your distribution.

3. **SDL2:** Install the SDL2 development package using the package manager for your Linux distribution. For example, on Ubuntu, open a terminal and run the following command:

   ```shell
   sudo apt-get update
   sudo apt-get install libsdl2-dev
   ```

   Adjust the command based on the package manager used in your distribution.

4. **Ninja:** To enhance the build performance, it is recommended to use Ninja as the build system. Install Ninja using the package manager for your Linux distribution. For example, on Ubuntu, open a terminal and run the following command:

   ```shell
   sudo apt-get update
   sudo apt-get install ninja-build
   ```

   Adjust the command based on the package manager used in your distribution.

Ensure that you follow the appropriate instructions for your specific operating system to install the necessary dependencies.

## Configuration

The E2D project provides several configuration options that can be set during the build process. These options are controlled via CMake variables. The following configuration options are available:

- `CMAKE_BUILD_TYPE`: Choose the type of build. Valid options are `Debug` or `Release`. The default build type is set to `Release`.
- `BUILD_SHARED_LIBS`: Set this variable to `ON` to build E2D as shared libraries or `OFF` to build it as static libraries. The default value is `ON`, which builds E2D as shared libraries.
- `E2D_BUILD_ENGINE`: Set this variable to `ON` to enable building the E2D library module called "Engine" or `OFF` to disable it. Building the "Engine" module is enabled by default.
- `E2D_BUILD_DOCS`: Set this variable to `ON` to enable generating documentation using Doxygen or `OFF` to disable it. Generating documentation is disabled by default.
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

To build and install the E2D project, follow these steps:

1. Clone the repository:
    ```shell
    git clone git@github.com:emilhornlund/E2D.git
    ```

2. Generate the build files using CMake:

   - **Windows:**

     If you're using Visual Studio as the compiler, open a command prompt or PowerShell and run the following command:

     ```shell
     cmake -S . -B build -G"Visual Studio 17 2022" -A Win32
     ```

     If you're using MinGW as the compiler, open a command prompt or PowerShell and run the following command:

     ```shell
     cmake -S . -B build -GNinja
     ```

   - **macOS:**

     Open a terminal and run the following command:

     ```shell
     cmake -S . -B build -GNinja
     ```

   - **Linux:**

     Open a terminal and run the following command:

     ```shell
     cmake -S . -B build -GNinja
     ```

   Adjust the command based on your operating system, compiler, and preferred CMake generator.

3. Build and install the project:

   - **Windows:**

     If you're using Visual Studio, open the generated solution file (`E2D.sln`) in Visual Studio. Build the project using the desired configuration (e.g., Release or Debug).

     If you're using MinGW or Ninja, open a command prompt or PowerShell and run the following command:

     ```shell
     cmake --build build --target install --config Release
     ```

   - **macOS and Linux:**

     Open a terminal and run the following command:

     ```shell
     cmake --build build --target install --config Release
     ```

   Adjust the command based on your operating system and preferred configuration.

   If you want to customize the installation directory, you can modify the CMAKE_INSTALL_PREFIX variable during the CMake configuration step:

   ```shell
   cmake -S . -B build -DCMAKE_INSTALL_PREFIX=<desired_installation_directory>
   ```

   Replace `<desired_installation_directory>` with the actual directory path you prefer. By default, the installation will use the system default prefix.

4. After the installation process completes, the E2D project libraries and related files will be installed in the specified directory or the default system directory.

Ensure that you follow the appropriate instructions for your specific operating system, compiler, and CMake generator when building and installing the project. Customize the `CMAKE_INSTALL_PREFIX` as needed to specify the desired installation directory.

## Packaging

To generate a package for the E2D project, you can use CPack, which is included with CMake. CPack provides various generators to create different package formats, such as ZIP, TGZ (TAR with gzip), RPM, DEB, and more.

To generate a package, run the following command after building the project:

```shell
cpack -G ZIP
```

This command will generate a ZIP package for the project. You can replace ZIP with the desired generator, such as TGZ for a TAR package with gzip compression.

You can specify multiple generators separated by commas to generate multiple package formats at once. For example:

```shell
cpack -G ZIP,TGZ
```

After running the cpack command, the package(s) will be generated in the current directory or the specified output directory, depending on your CPack configuration.

Make sure to adjust the generator and other options according to your project's needs.

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

## Generating Documentation

E2D supports generating documentation using Doxygen. To enable documentation generation during the build process, set the `E2D_BUILD_DOCS` CMake variable to ON:

```shell
cmake -DE2D_BUILD_DOCS=ON ...
```

Once the project is built, you can generate the documentation by running the `e2d-tools-docs` target:

```shell
cmake --build build --target e2d-tools-docs
```

The generated documentation will be available in the `docs` directory.

### Instructions for Installing Doxygen:

#### Windows Doxygen Installation
1. Download the Doxygen installer from the official [Doxygen website](https://www.doxygen.nl/download.html).
2. Run the installer and follow the on-screen instructions to complete the installation.
3. If you plan to generate HTML Help documentation, ensure that you have the HTML Help Compiler program (hhc.exe) installed. You can download it from the [HTML Help Workshop](https://www.microsoft.com/en-us/download/details.aspx?id=21138) page.

#### macOS Doxygen Installation
Install Doxygen using Homebrew by running the following command in the terminal:

```shell
brew install doxygen
```

#### Linux Doxygen Installation
Install Doxygen using the package manager for your Linux distribution. For example, on Ubuntu, you can run the following command:

```shell
sudo apt-get install doxygen
```

On Fedora, use the following command:

```shell
sudo dnf install doxygen
```

Adjust the command based on the package manager used in your distribution.

Ensure that Doxygen is installed and available in the system's executable search path before configuring and building the project.

## Code Quality

In the E2D project, we strive for high code quality to ensure maintainability and readability. We have implemented two tools, **clang-tidy** and **clang-format**, to assist in achieving this goal. These tools help us identify and fix potential issues with our C++ code, ensuring adherence to best practices and coding standards.

### Clang-Tidy

Clang-Tidy is a powerful tool that performs static analysis on our C++ code. It helps us identify potential bugs, stylistic issues, and other code quality problems. By integrating Clang-Tidy into our development workflow, we can catch issues early and maintain a consistent and clean codebase.

To run Clang-Tidy, we have created a CMake target named **e2d-tools-tidy**. You can invoke this target by running the following command from the build directory:

```shell
cmake --build . --target e2d-tools-tidy
```

Running the **e2d-tools-tidy** target will analyze the source code using Clang-Tidy and provide a report of any identified issues. It is essential to regularly run this target during development to ensure the code meets our quality standards.

### Clang-Format

Clang-Format is a tool that automatically formats our C++ code according to a predefined set of rules. It enforces a consistent coding style across the entire codebase, improving readability and reducing the chance of introducing formatting errors.

To apply Clang-Format to our codebase, we have created a CMake target named **e2d-tools-format**. You can run this target by executing the following command from the build directory:

```shell
cmake --build . --target e2d-tools-format
```

Running the **e2d-tools-format** target will automatically format the source code files using Clang-Format. It will modify the files in place, ensuring that the code follows the defined coding style.

By regularly running the **e2d-tools-format** target, we can maintain a consistent coding style throughout the project and reduce unnecessary code changes during code reviews.

It is recommended to run both the **e2d-tools-tidy** and **e2d-tools-format** targets before committing any changes to the repository. This ensures that our codebase remains clean, well-formatted, and adheres to the highest quality standards.

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
