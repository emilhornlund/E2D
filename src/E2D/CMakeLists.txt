# include the E2D specific macros
include(${PROJECT_SOURCE_DIR}/cmake/Macros.cmake)

# define the path of our additional CMake modules
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules/")

# set the output directory for E2D libraries
set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")

add_subdirectory(Core)
