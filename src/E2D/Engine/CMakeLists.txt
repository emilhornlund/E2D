set(INCROOT ${PROJECT_SOURCE_DIR}/include/E2D/Engine)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/E2D/Engine)

set(SRC
    ${INCROOT}/Application.hpp
    ${SRCROOT}/Application.cpp
    ${INCROOT}/Export.hpp
)

e2d_add_library(Engine SOURCES ${SRC})

target_link_libraries(e2d-engine PUBLIC E2D::Core)

target_link_libraries(e2d-engine PRIVATE SDL2)

if(E2D_OS_WINDOWS)
    if(ARCH_32BITS)
        add_custom_command(TARGET e2d-engine POST_BUILD
                           COMMAND ${CMAKE_COMMAND} -E copy_if_different
                           "${PROJECT_SOURCE_DIR}/extlibs/bin/x86/SDL2.dll"
                           $<TARGET_FILE_DIR:e2d-engine>)
    elseif(ARCH_64BITS)
        add_custom_command(TARGET e2d-engine POST_BUILD
                           COMMAND ${CMAKE_COMMAND} -E copy_if_different
                           "${PROJECT_SOURCE_DIR}/extlibs/bin/x64/SDL2.dll"
                           $<TARGET_FILE_DIR:e2d-engine>)
    endif()
endif()
