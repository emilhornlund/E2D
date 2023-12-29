set(TARGET e2d-core)

set(INCROOT ${PROJECT_SOURCE_DIR}/include/E2D/Core)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/E2D/Core)

set(SRC
    ${INCROOT}/Color.hpp
    ${INCROOT}/Color.inl
    ${INCROOT}/Export.hpp
    ${INCROOT}/NonCopyable.hpp
    ${INCROOT}/Rect.hpp
    ${INCROOT}/Rect.inl
    ${INCROOT}/Timer.hpp
    ${SRCROOT}/Timer.cpp
    ${INCROOT}/Vector2.hpp
    ${INCROOT}/Vector2.inl
)

e2d_add_library(Core SOURCES ${SRC})

target_link_libraries(${TARGET} PRIVATE SDL2)

if(E2D_OS_WINDOWS)
    if(ARCH_32BITS)
        add_custom_command(TARGET ${TARGET} POST_BUILD
                           COMMAND ${CMAKE_COMMAND} -E copy_if_different
                           "${PROJECT_SOURCE_DIR}/extlibs/bin/x86/SDL2.dll"
                           $<TARGET_FILE_DIR:${TARGET}>)
    elseif(ARCH_64BITS)
        add_custom_command(TARGET ${TARGET} POST_BUILD
                           COMMAND ${CMAKE_COMMAND} -E copy_if_different
                           "${PROJECT_SOURCE_DIR}/extlibs/bin/x64/SDL2.dll"
                           $<TARGET_FILE_DIR:${TARGET}>)
    endif()
endif()
