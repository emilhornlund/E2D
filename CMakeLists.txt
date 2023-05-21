cmake_minimum_required(VERSION 3.22)
project(E2D VERSION 1.0.0)

include(cmake/Config.cmake)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")

set(CMAKE_CXX_STANDARD 20)

if(E2D_OS_WINDOWS)
    list(APPEND CMAKE_INCLUDE_PATH "${PROJECT_SOURCE_DIR}/extlibs/headers")
    if(E2D_COMPILER_GCC OR (E2D_COMPILER_CLANG AND MINGW))
        if(ARCH_32BITS)
            list(APPEND CMAKE_LIBRARY_PATH "${PROJECT_SOURCE_DIR}/extlibs/libs-mingw/x86")
            list(APPEND CMAKE_LIBRARY_PATH "${PROJECT_SOURCE_DIR}/extlibs/bin/x86")
        elseif(ARCH_64BITS)
            list(APPEND CMAKE_LIBRARY_PATH "${PROJECT_SOURCE_DIR}/extlibs/libs-mingw/x64")
            list(APPEND CMAKE_LIBRARY_PATH "${PROJECT_SOURCE_DIR}/extlibs/bin/x64")
        endif()
    endif()
endif()

find_package(SDL2 REQUIRED)

add_executable(e2d main.cpp)
target_include_directories(e2d PRIVATE ${SDL2_INCLUDE_DIR})
target_link_libraries(e2d PRIVATE ${SDL2_LIBRARY})
