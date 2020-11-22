set(INC_ROOT ${PROJECT_SOURCE_DIR}/examples/basic/include/Basic)
set(SRC_ROOT ${PROJECT_SOURCE_DIR}/examples/basic/src/Basic)

set(SRC_FILES
    ${SRC_ROOT}/BasicApplication.cpp
    ${INC_ROOT}/BasicApplication.hpp
    ${SRC_ROOT}/main.cpp
)

set(TARGET_NAME e2d-example-basic)

e2d_add_example(${TARGET_NAME}
    SOURCES ${SRC_FILES}
    INCLUDE ${PROJECT_SOURCE_DIR}/examples/basic/include
    DEPENDS e2d-core
)
