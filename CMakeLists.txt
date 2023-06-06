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

include(GNUInstallDirs)

e2d_set_option(BUILD_SHARED_LIBS TRUE BOOL "TRUE to build E2D as shared libraries, FALSE to build it as static libraries (default: TRUE)")

if(E2D_OS_MACOS)
    e2d_set_option(E2D_BUILD_FRAMEWORKS FALSE BOOL "TRUE to build E2D as frameworks libraries (release only), FALSE to build according to BUILD_SHARED_LIBS (default: FALSE)")
endif()

e2d_set_option(E2D_BUILD_ENGINE TRUE BOOL "TRUE to build E2D's Engine module. (default: TRUE)")

e2d_set_option(E2D_USE_SYSTEM_DEPS FALSE BOOL "TRUE to use system dependencies, FALSE to use the bundled ones. (default: FALSE)")
if(E2D_USE_SYSTEM_DEPS)
    file(GLOB_RECURSE DEP_LIBS    "${PROJECT_SOURCE_DIR}/extlibs/libs*/*")
    file(GLOB_RECURSE DEP_BINS    "${PROJECT_SOURCE_DIR}/extlibs/bin*/*")
    file(GLOB_RECURSE DEP_HEADERS "${PROJECT_SOURCE_DIR}/extlibs/headers/*")

    foreach(DEP_FILE ${DEP_LIBS} ${DEP_BINS} ${DEP_HEADERS})
        get_filename_component(DEP_DIR ${DEP_FILE} PATH)
        list(APPEND CMAKE_IGNORE_PATH "${DEP_DIR}")
        get_filename_component(DEP_PARENT_DIR ${DEP_DIR} PATH)
        while(NOT DEP_PARENT_DIR STREQUAL "${PROJECT_SOURCE_DIR}/extlibs")
            list(APPEND CMAKE_IGNORE_PATH "${DEP_PARENT_DIR}")
            get_filename_component(DEP_PARENT_DIR ${DEP_PARENT_DIR} PATH)
        endwhile()
    endforeach()

    list(REMOVE_DUPLICATES CMAKE_IGNORE_PATH)
endif()

if(E2D_COMPILER_MSVC)
    e2d_set_option(E2D_GENERATE_PDB TRUE BOOL "True to generate PDB debug symbols, FALSE otherwise.")
endif()

if(E2D_OS_WINDOWS)
    e2d_set_option(E2D_USE_STATIC_STD_LIBS FALSE BOOL "TRUE to statically link to the standard libraries, FALSE to use them as DLLs")

    if(BUILD_SHARED_LIBS AND E2D_USE_STATIC_STD_LIBS)
        message(FATAL_ERROR "BUILD_SHARED_LIBS and E2D_USE_STATIC_STD_LIBS cannot be used together")
    endif()
endif()

if(E2D_OS_MACOS)
    if(E2D_BUILD_FRAMEWORKS)
        if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
            message(FATAL_ERROR "CMAKE_BUILD_TYPE should be \"Release\" when E2D_BUILD_FRAMEWORKS is TRUE")
            return()
        endif()

        if(NOT BUILD_SHARED_LIBS)
            message(FATAL_ERROR "BUILD_SHARED_LIBS should be TRUE when E2D_BUILD_FRAMEWORKS is TRUE")
            return()
        endif()
    endif()
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(src/E2D)

e2d_set_option(E2D_BUILD_DOCS FALSE BOOL "TRUE to generate the API documentation, FALSE to ignore it (default: false)")
if(E2D_BUILD_DOCS)
    add_subdirectory(docs)
endif()

e2d_set_option(E2D_BUILD_EXAMPLES FALSE BOOL "TRUE to build the E2D examples, FALSE to ignore them (default: FALSE)")
if(E2D_BUILD_EXAMPLES AND NOT E2D_OS_ANDROID)
    add_subdirectory(examples)
endif()

if(NOT E2D_BUILD_FRAMEWORKS)
    install(DIRECTORY include/
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
            COMPONENT devel
            FILES_MATCHING PATTERN "*.hpp" PATTERN "*.inl")

    if(E2D_GENERATE_PDB)
        install(DIRECTORY ${PROJECT_BINARY_DIR}/lib/
                DESTINATION ${CMAKE_INSTALL_LIBDIR}
                COMPONENT devel
                FILES_MATCHING PATTERN "*.pdb")
    endif()
else()
    file(GLOB E2D_HEADERS RELATIVE ${PROJECT_SOURCE_DIR} "include/E2D/*")

    set_property(GLOBAL PROPERTY XCODE_EMIT_EFFECTIVE_PLATFORM_NAME OFF)

    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/dummy.cpp
                       COMMAND touch ${CMAKE_CURRENT_BINARY_DIR}/dummy.cpp
                       VERBATIM)

    set(E2D_SOURCES ${E2D_HEADERS})
    list(APPEND E2D_SOURCES ${CMAKE_CURRENT_BINARY_DIR}/dummy.cpp)

    add_library(E2D ${E2D_SOURCES})

    target_compile_features(E2D PUBLIC cxx_std_20)

    e2d_set_stdlib(E2D)

    set_target_properties(E2D PROPERTIES
                          FRAMEWORK TRUE
                          FRAMEWORK_VERSION ${PROJECT_VERSION}
                          MACOSX_FRAMEWORK_IDENTIFIER com.emilhornlund.E2D
                          MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${PROJECT_VERSION}
                          MACOSX_FRAMEWORK_BUNDLE_VERSION ${PROJECT_VERSION}
                          PUBLIC_HEADER "${E2D_HEADERS}")

    add_custom_command(TARGET E2D POST_BUILD COMMAND cp -r
                      ${PROJECT_SOURCE_DIR}/include/E2D/Config.hpp
                      ${PROJECT_SOURCE_DIR}/include/E2D/Core.hpp
                      ${PROJECT_SOURCE_DIR}/include/E2D/Core
                      $<TARGET_FILE_DIR:E2D>/Headers
                      VERBATIM)

    if(E2D_BUILD_ENGINE)
        add_custom_command(TARGET E2D POST_BUILD COMMAND cp -r
                           ${PROJECT_SOURCE_DIR}/include/E2D/Engine.hpp
                           ${PROJECT_SOURCE_DIR}/include/E2D/Engine
                           $<TARGET_FILE_DIR:E2D>/Headers
                           VERBATIM)
    endif()

    set_target_properties(E2D PROPERTIES INSTALL_NAME_DIR "@rpath")
    if(NOT CMAKE_SKIP_BUILD_RPATH)
        set_target_properties(${target} PROPERTIES BUILD_WITH_INSTALL_NAME_DIR TRUE)
    endif()

    install(TARGETS E2D
            FRAMEWORK DESTINATION "."
            COMPONENT devel)
endif()

install(FILES LICENSE DESTINATION ${CMAKE_INSTALL_DOCDIR})
install(FILES README.md DESTINATION ${CMAKE_INSTALL_DOCDIR})

if(E2D_OS_WINDOWS)
    if(NOT E2D_USE_SYSTEM_DEPS)
        if(ARCH_32BITS)
            install(DIRECTORY extlibs/bin/x86/ DESTINATION ${CMAKE_INSTALL_BINDIR})
            if(E2D_COMPILER_MSVC OR (E2D_COMPILER_CLANG AND NOT MINGW))
                install(DIRECTORY extlibs/libs-msvc/x86/ DESTINATION ${CMAKE_INSTALL_LIBDIR})
            else()
                install(DIRECTORY extlibs/libs-mingw/x86/ DESTINATION ${CMAKE_INSTALL_LIBDIR})
            endif()
        elseif(ARCH_64BITS)
            install(DIRECTORY extlibs/bin/x64/ DESTINATION ${CMAKE_INSTALL_BINDIR})
            if(E2D_COMPILER_MSVC OR (E2D_COMPILER_CLANG AND NOT MINGW))
                install(DIRECTORY extlibs/libs-msvc/x64/ DESTINATION ${CMAKE_INSTALL_LIBDIR})
            else()
                install(DIRECTORY extlibs/libs-mingw/x64/ DESTINATION ${CMAKE_INSTALL_LIBDIR})
            endif()
        endif()
    endif()
elseif(E2D_OS_MACOS)
    if(SDL2 STREQUAL "${PROJECT_SOURCE_DIR}/extlibs/libs-macos/Frameworks/SDL2.framework")
        install(DIRECTORY extlibs/libs-macos/Frameworks/SDL2.framework DESTINATION ${CMAKE_INSTALL_LIBDIR})
    endif()
endif()

e2d_export_targets()

set(CPACK_PACKAGE_NAME "E2D")
set(CPACK_PACKAGE_VENDOR "Emil Hörnlund")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "E2D is a 2D game engine written in C++20 using SDL2")
set(CPACK_PACKAGE_FILE_NAME "E2D-${PROJECT_VERSION}-${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}-${CMAKE_BUILD_TYPE}")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "E2D ${PROJECT_VERSION}")
set(CPACK_MONOLITHIC_INSTALL ON)

include(CPack)

e2d_set_option(E2D_BUILD_TEST_SUITE FALSE BOOL "TRUE to build the E2D test suite, FALSE to ignore it")
if(E2D_BUILD_TEST_SUITE)
    if(E2D_BUILD_ENGINE)
        enable_testing()
        add_subdirectory(test)
    else()
        message(WARNING "Cannot build unit testing unless all modules are enabled")
    endif()
endif()

e2d_set_option(CLANG_FORMAT_EXECUTABLE clang-format STRING "Override clang-format executable, requires version 12, 13, or 14")
add_custom_target(e2d-tools-format
                  COMMAND ${CMAKE_COMMAND} -DCLANG_FORMAT_EXECUTABLE=${CLANG_FORMAT_EXECUTABLE} -P ./cmake/Format.cmake
                  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} VERBATIM)

e2d_set_option(CLANG_TIDY_EXECUTABLE clang-tidy STRING "Override clang-tidy executable, requires minimum version 14")
add_custom_target(e2d-tools-tidy
                  COMMAND ${CMAKE_COMMAND} -DCLANG_TIDY_EXECUTABLE=${CLANG_TIDY_EXECUTABLE} -DPROJECT_BINARY_DIR=${PROJECT_BINARY_DIR} -P ./cmake/Tidy.cmake
                  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} VERBATIM)
