set(INCROOT ${PROJECT_SOURCE_DIR}/include/E2D/Core)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/E2D/Core)

set(SRC
    ${INCROOT}/Color.hpp
    ${INCROOT}/Color.inl
    ${INCROOT}/Export.hpp
    ${INCROOT}/NonCopyable.hpp
)

e2d_add_library(Core STATIC SOURCES ${SRC} ${SRCROOT}/dummy.cpp)
