set(INCROOT ${PROJECT_SOURCE_DIR}/include/E2D/Core)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/E2D/Core)

set(SRC
    ${INCROOT}/Color.hpp
    ${INCROOT}/Color.inl
    ${INCROOT}/Export.hpp
    ${INCROOT}/NonCopyable.hpp
    ${INCROOT}/Timer.hpp
    ${SRCROOT}/Timer.cpp
)

e2d_add_library(Core SOURCES ${SRC})

target_link_libraries(e2d-core PRIVATE SDL2)

if(E2D_OS_WINDOWS)
    if(ARCH_32BITS)
        add_custom_command(TARGET e2d-core POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${PROJECT_SOURCE_DIR}/extlibs/bin/x86/SDL2.dll"
                $<TARGET_FILE_DIR:e2d-core>)
    elseif(ARCH_64BITS)
        add_custom_command(TARGET e2d-core POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${PROJECT_SOURCE_DIR}/extlibs/bin/x64/SDL2.dll"
                $<TARGET_FILE_DIR:e2d-core>)
    endif()
endif()
