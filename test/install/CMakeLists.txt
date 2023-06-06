cmake_minimum_required(VERSION 3.22)
project(e2d-test-install CXX)

# This skips the find_package call when building via add_subdirectory since that will fail under those circumstances
if(PROJECT_IS_TOP_LEVEL)
    if(NOT BUILD_SHARED_LIBS)
        set(E2D_STATIC_LIBRARIES TRUE)
    endif()

    find_package(E2D 1.0.0 EXACT CONFIG REQUIRED COMPONENTS Engine)
endif()

add_executable(e2d-test-install Install.cpp)
target_link_libraries(e2d-test-install PRIVATE E2D::Engine)
