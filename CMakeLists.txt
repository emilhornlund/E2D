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

if(E2D_COMPILER_MSVC)
    e2d_set_option(E2D_GENERATE_PDB TRUE BOOL "True to generate PDB debug symbols, FALSE otherwise.")
endif()

if(E2D_OS_WINDOWS)
    e2d_set_option(E2D_USE_STATIC_STD_LIBS FALSE BOOL "TRUE to statically link to the standard libraries, FALSE to use them as DLLs")
    
    if(BUILD_SHARED_LIBS AND E2D_USE_STATIC_STD_LIBS)
        message(FATAL_ERROR "BUILD_SHARED_LIBS and E2D_USE_STATIC_STD_LIBS cannot be used together")
    endif()
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(src/E2D)
add_subdirectory(examples)
