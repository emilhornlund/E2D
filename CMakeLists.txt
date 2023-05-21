cmake_minimum_required(VERSION 3.22)
project(E2D VERSION 1.0.0)

include(cmake/Config.cmake)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)

add_executable(e2d main.cpp)
target_include_directories(e2d PRIVATE ${SDL2_INCLUDE_DIR})
target_link_libraries(e2d PRIVATE ${SDL2_LIBRARY})
