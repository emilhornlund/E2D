include(CTest)

set(SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

add_subdirectory(E2D/Core)

e2d_add_test(e2d-tests
    SOURCES ${SRC_FILES}
    DEPENDS e2d-core
)

target_include_directories(e2d-tests PRIVATE ${PROJECT_SOURCE_DIR}/extlibs/headers)
