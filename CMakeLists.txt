cmake_minimum_required(VERSION 3.16)

# add some default value for some additional macOS variable
# note that those variables are ignored on other systems
if(NOT CMAKE_OSX_ARCHITECTURES)
    set(CMAKE_OSX_ARCHITECTURES "x86_64" CACHE STRING "macOS architecture to build; 64-bit is expected" FORCE)
endif()
if(NOT CMAKE_OSX_SYSROOT)
    # query the path to the default SDK, will fail on non-macOS, but it's okay.
    execute_process(
        COMMAND xcodebuild -sdk macosx -version Path
        COMMAND head -n 1
        COMMAND tr -d '\n'
        OUTPUT_VARIABLE CMAKE_OSX_SYSROOT
        ERROR_QUIET
    )
endif()

project(e2d
    VERSION 0.1.0
    LANGUAGES C CXX
)

# set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'RelWithDebInfo' as none was specified.")
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
    # set the possible values of build type for cmake-gui, ccmake
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Generate compile_commands.json to make it easier to work with clang based tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# make sure the user doesn't play dirty with symlinks
get_filename_component(SRC_DIR "${CMAKE_SOURCE_DIR}" REALPATH)
get_filename_component(BIN_DIR "${CMAKE_BINARY_DIR}" REALPATH)

# disallow in-source builds
if("${SRC_DIR}" STREQUAL "${BIN_DIR}")
    message(FATAL_ERROR "Quitting configuration - in-source builds are disabled")
endif()

# include the configuration file
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# add an option for choosing the build type (shared or static)
option(BUILD_SHARED_LIBS "Build E2D as shared libraries. (default: ON)" ON)

# add an option for building the examples
option(E2D_BUILD_EXAMPLES "Build the E2D examples. (default: OFF)" OFF)

# add an option for building the API documentation
option(E2D_BUILD_DOCS "Build the E2D API documentation. (default OFF)" OFF)

# add an option for building the tests
option(E2D_BUILD_TESTS "Build the E2D tests. (default: OFF)" OFF)

if(E2D_OS_MACOSX)
    # add an option for building E2D as frameworks
    option(E2D_BUILD_FRAMEWORKS "Build E2D as framework libraries on MacOS. (default: OFF)" OFF)

    if(E2D_BUILD_FRAMEWORKS)
        # requirement #1
        if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
            message(FATAL_ERROR "CMAKE_BUILD_TYPE should be \"Release\" when E2D_BUILD_FRAMEWORKS is ON")
            return()
        endif()

        # requirement #2
        if(NOT BUILD_SHARED_LIBS)
            message(FATAL_ERROR "BUILD_SHARED_LIBS should be ON when E2D_BUILD_FRAMEWORKS is ON")
            return()
        endif()
    endif()

    # only the default architecture (i.e. 64-bit) is supported
    if(NOT CMAKE_OSX_ARCHITECTURES STREQUAL "x86_64")
        message(FATAL_ERROR "Only 64-bit architecture is supported")
    endif()
endif()

# add an option for choosing the build type (shared or static)
option(E2D_ENABLE_IPO "Enable Interprocedural Optimization, aka Link Time Optimization (LTO). (default: OFF)" OFF)
if(E2D_ENABLE_IPO)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT IPO_RESULT OUTPUT IPO_OUTPUT)
    if(IPO_RESULT)
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
    else()
        message(SEND_ERROR "IPO is not supported: ${IPO_OUTPUT}")
    endif()
endif()

# add an option for setting sanitizer options if supported by compiler
option(E2D_ENABLE_COVERAGE "Enable coverage reporting for gcc/clang. (default OFF)" OFF)

add_subdirectory(src/E2D)

if(E2D_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(E2D_BUILD_DOCS)
    set(DOXYGEN_CALLER_GRAPH YES)
    set(DOXYGEN_CALL_GRAPH YES)
    set(DOXYGEN_EXTRACT_ALL YES)
    set(DOXYGEN_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/docs)

    set(INPUTS
        "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_SOURCE_DIR}/src"
        "${PROJECT_SOURCE_DIR}/examples"
    )

    find_package(Doxygen REQUIRED dot)

    doxygen_add_docs(e2d-docs ${INPUTS})
endif()

if(E2D_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

e2d_export_targets()
