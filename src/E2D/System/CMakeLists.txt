set(INC_ROOT ${PROJECT_SOURCE_DIR}/include/E2D/System)
set(SRC_ROOT ${PROJECT_SOURCE_DIR}/src/E2D/System)

set(SRC_FILES
    ${INC_ROOT}.hpp
    ${INC_ROOT}/Export.hpp
    ${INC_ROOT}/Vector2.hpp
)

e2d_add_library(e2d-system
    SOURCES ${SRC_FILES}
)
