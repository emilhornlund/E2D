include(FetchContent)

set(CATCH_CONFIG_FAST_COMPILE ON CACHE BOOL "")
FetchContent_Declare(Catch2
                     GIT_REPOSITORY https://github.com/catchorg/Catch2.git
                     GIT_TAG v3.3.2)
FetchContent_MakeAvailable(Catch2)
include(Catch)

target_compile_features(Catch2 PRIVATE cxx_std_20)

set_target_properties(Catch2 PROPERTIES COMPILE_OPTIONS "" EXPORT_COMPILE_COMMANDS OFF)
set_target_properties(Catch2WithMain PROPERTIES EXPORT_COMPILE_COMMANDS OFF)
get_target_property(CATCH2_INCLUDE_DIRS Catch2 INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(Catch2 SYSTEM INTERFACE ${CATCH2_INCLUDE_DIRS})

# E2D Core Library Tests
set(CORE_SRC
    Core/Color.test.cpp
)
e2d_add_test(e2d-test-core "${CORE_SRC}" E2D::Core)

# E2D Engine Library Tests
set(ENGINE_SRC
    Engine/Application.test.cpp
)
e2d_add_test(e2d-test-engine "${ENGINE_SRC}" E2D::Engine)

if(E2D_OS_WINDOWS)
    if(ARCH_32BITS)
        add_custom_command(TARGET e2d-test-engine PRE_BUILD
                           COMMAND ${CMAKE_COMMAND} -E copy_if_different
                           "${PROJECT_SOURCE_DIR}/extlibs/bin/x86/SDL2.dll"
                           $<TARGET_FILE_DIR:e2d-test-engine>)
    elseif(ARCH_64BITS)
        add_custom_command(TARGET e2d-test-engine PRE_BUILD
                           COMMAND ${CMAKE_COMMAND} -E copy_if_different
                           "${PROJECT_SOURCE_DIR}/extlibs/bin/x64/SDL2.dll"
                           $<TARGET_FILE_DIR:e2d-test-engine>)
    endif()
endif()

add_custom_target(runtests DEPENDS e2d-test-core e2d-test-engine)
add_custom_command(TARGET runtests
                   COMMENT "Run tests"
                   POST_BUILD COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure -C $<CONFIG>
                   VERBATIM)
