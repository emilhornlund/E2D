set(TARGET e2d-engine)

set(INCROOT ${PROJECT_SOURCE_DIR}/include/E2D/Engine)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/E2D/Engine)

set(SRC
    ${INCROOT}/Application.hpp
    ${SRCROOT}/Application.cpp
    ${INCROOT}/Export.hpp
    ${INCROOT}/Entity.hpp
    ${SRCROOT}/Entity.cpp
    ${INCROOT}/Object.hpp
    ${SRCROOT}/Object.cpp
    ${INCROOT}/ObjectRegistry.hpp
    ${SRCROOT}/ObjectRegistry.cpp
    ${INCROOT}/Renderable.hpp
    ${INCROOT}/Renderer.hpp
    ${SRCROOT}/Renderer.cpp
    ${SRCROOT}/RendererImpl.hpp
    ${SRCROOT}/RendererImpl.cpp
    ${SRCROOT}/RenderQueue.hpp
    ${SRCROOT}/RenderQueue.cpp
    ${SRCROOT}/SDLRenderUtils.hpp
    ${SRCROOT}/SDLRenderUtils.cpp
    ${INCROOT}/Sprite.hpp
    ${SRCROOT}/Sprite.cpp
    ${INCROOT}/Texture.hpp
    ${SRCROOT}/Texture.cpp
    ${SRCROOT}/TextureImpl.hpp
    ${SRCROOT}/TextureImpl.cpp
    ${INCROOT}/Window.hpp
    ${SRCROOT}/Window.cpp
    ${SRCROOT}/WindowImpl.hpp
    ${SRCROOT}/WindowImpl.cpp
)

e2d_add_library(Engine SOURCES ${SRC})

target_link_libraries(${TARGET} PUBLIC E2D::Core)

target_link_libraries(${TARGET} PRIVATE SDL2 SDL2_IMAGE SDL2_TTF)

if(E2D_OS_WINDOWS)
    set(DLL_NAMES SDL2 SDL2_image SDL2_ttf)

    foreach(DLL_NAME ${DLL_NAMES})
        if(ARCH_32BITS)
            set(DLL_SOURCE "${PROJECT_SOURCE_DIR}/extlibs/bin/x86/${DLL_NAME}.dll")
        elseif(ARCH_64BITS)
            set(DLL_SOURCE "${PROJECT_SOURCE_DIR}/extlibs/bin/x64/${DLL_NAME}.dll")
        endif()

        add_custom_command(TARGET ${TARGET} PRE_BUILD
                           COMMAND ${CMAKE_COMMAND} -E copy_if_different
                           "${DLL_SOURCE}"
                           $<TARGET_FILE_DIR:${TARGET}>)
    endforeach()
endif()
