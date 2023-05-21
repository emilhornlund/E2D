set(SRC main.cpp)

e2d_add_example(e2d-example-hello-world
                SOURCES ${SRC}
                DEPENDS E2D::Engine)
