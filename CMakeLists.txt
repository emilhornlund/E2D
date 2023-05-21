cmake_minimum_required(VERSION 3.22)

macro(e2d_set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

e2d_set_option(CMAKE_BUILD_TYPE Release STRING "Choose the type of build (Debug or Release)")

project(E2D VERSION 1.0.0)

include(cmake/Config.cmake)

e2d_set_option(BUILD_SHARED_LIBS TRUE BOOL "TRUE to build E2D as shared libraries, FALSE to build it as static libraries (default: TRUE)")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(src/E2D)
add_subdirectory(examples)
