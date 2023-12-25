set(SRC main.cpp)

set(RSC_ROOT ${PROJECT_SOURCE_DIR}/examples/hello-world)

set(RESOURCES
    ${RSC_ROOT}/gabe-idle-run.png
)

e2d_add_example(e2d-example-hello-world
                SOURCES ${SRC}
                DEPENDS E2D::Engine
                RESOURCES ${RESOURCES})
