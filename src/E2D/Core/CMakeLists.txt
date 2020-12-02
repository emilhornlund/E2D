set(INC_ROOT ${PROJECT_SOURCE_DIR}/include/E2D/Core)
set(SRC_ROOT ${PROJECT_SOURCE_DIR}/src/E2D/Core)

set(SRC_FILES
    ${INC_ROOT}.hpp
    ${SRC_ROOT}/Application.cpp
    ${INC_ROOT}/Application.hpp
    ${SRC_ROOT}/EventHandler.cpp
    ${SRC_ROOT}/EventHandler.hpp
    ${INC_ROOT}/Export.hpp
    ${SRC_ROOT}/Window.cpp
    ${INC_ROOT}/Window.hpp
)

e2d_add_library(e2d-core
    SOURCES ${SRC_FILES}
    DEPENDS e2d-system
)

e2d_find_package(SDL2
    INCLUDE SDL2_INCLUDE_DIRS
    LINK SDL2_LIBRARIES
)

target_link_libraries(e2d-core PUBLIC SDL2)
