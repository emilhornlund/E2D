
set(ROOT ${PROJECT_SOURCE_DIR}/examples/classic-rpg)

set(SRC
    ${ROOT}/main.cpp
    ${ROOT}/ClassicRPG.hpp
    ${ROOT}/ClassicRPG.cpp
    ${ROOT}/GameScene.hpp
    ${ROOT}/GameScene.cpp
    ${ROOT}/Player.hpp
    ${ROOT}/Player.cpp
)

set(RESOURCES
    ${ROOT}/classic-rpg-player.png
)

e2d_add_example(e2d-example-classic-rpg
        SOURCES ${SRC}
        DEPENDS E2D::Engine
        RESOURCES ${RESOURCES})
