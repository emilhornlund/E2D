include(FetchContent)

add_subdirectory(install)
e2d_set_target_warnings(e2d-test-install)

set(CATCH_CONFIG_FAST_COMPILE ON CACHE BOOL "")
FetchContent_Declare(Catch2
                     GIT_REPOSITORY https://github.com/catchorg/Catch2.git
                     GIT_TAG v3.5.0
                     GIT_SHALLOW ON)
FetchContent_MakeAvailable(Catch2)
include(Catch)

target_compile_features(Catch2 PRIVATE cxx_std_17)

set_target_properties(Catch2 PROPERTIES COMPILE_OPTIONS "" EXPORT_COMPILE_COMMANDS OFF)
set_target_properties(Catch2WithMain PROPERTIES EXPORT_COMPILE_COMMANDS OFF)
get_target_property(CATCH2_INCLUDE_DIRS Catch2 INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(Catch2 SYSTEM INTERFACE ${CATCH2_INCLUDE_DIRS})

# E2D Core Library Tests
set(CORE_SRC
    Core/Color.test.cpp
    Core/Timer.test.cpp
)
e2d_add_test(e2d-test-core "${CORE_SRC}" E2D::Core)

# E2D Engine Library Tests
set(ENGINE_SRC
    Engine/Application.test.cpp
    Engine/Renderer.test.cpp
    Engine/RendererQueue.test.cpp
    Engine/Texture.test.cpp
    Engine/Window.test.cpp
)
e2d_add_test(e2d-test-engine "${ENGINE_SRC}" E2D::Engine)

if(E2D_OS_WINDOWS)
    set(DLL_NAMES SDL2 SDL2_image SDL2_ttf)

    foreach(DLL_NAME ${DLL_NAMES})
        if(ARCH_32BITS)
            set(DLL_SOURCE "${PROJECT_SOURCE_DIR}/extlibs/bin/x86/${DLL_NAME}.dll")
        elseif(ARCH_64BITS)
            set(DLL_SOURCE "${PROJECT_SOURCE_DIR}/extlibs/bin/x64/${DLL_NAME}.dll")
        endif()

        add_custom_command(TARGET e2d-test-core PRE_BUILD
                           COMMAND ${CMAKE_COMMAND} -E copy_if_different
                           "${DLL_SOURCE}"
                           $<TARGET_FILE_DIR:e2d-test-core>)
    endforeach()
endif()

add_custom_target(runtests DEPENDS e2d-test-core e2d-test-engine)
add_custom_command(TARGET runtests
                   COMMENT "Run tests"
                   POST_BUILD COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure -C $<CONFIG>
                   VERBATIM)
