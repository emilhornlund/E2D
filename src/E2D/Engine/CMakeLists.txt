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
