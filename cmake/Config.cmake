if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(E2D_OS_LINUX 1)
else()
    message(FATAL_ERROR "Unsupported operating system or environment")
    return()
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
    set(E2D_COMPILER_GCC 1)
    execute_process(COMMAND "${CMAKE_CXX_COMPILER}" "--version" OUTPUT_VARIABLE GCC_COMPILER_VERSION)
    string(REGEX MATCHALL ".*(tdm[64]*-[1-9]).*" E2D_COMPILER_GCC_TDM "${GCC_COMPILER_VERSION}")
else()
    message(FATAL_ERROR "Unsupported compiler")
    return()
endif()
