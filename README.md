# E2D

My own, Emil's 2D (E2D) game engine written in C++20 using SDL2.

## Prerequisites

Before building and running the E2D project, ensure you have the following prerequisites:

- C++20 compiler: E2D requires a compiler that supports the C++20 standard.
- CMake 3.22 or higher: E2D uses CMake as the build system. Make sure you have CMake version 3.22 or higher installed on your system. You can download CMake from the [official CMake website](https://cmake.org/download/).

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