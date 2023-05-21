macro(e2d_add_library module)
    cmake_parse_arguments(THIS "STATIC" "" "SOURCES" ${ARGN})
    if(NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments when calling e2d_add_library: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    string(TOLOWER e2d-${module} target)
    if(THIS_STATIC)
        add_library(${target} STATIC ${THIS_SOURCES})
    else()
        add_library(${target} ${THIS_SOURCES})
    endif()
    add_library(E2D::${module} ALIAS ${target})

    target_compile_features(${target} PUBLIC cxx_std_20)

    string(REPLACE "-" "_" NAME_UPPER "${target}")
    string(TOUPPER "${NAME_UPPER}" NAME_UPPER)
    set_target_properties(${target} PROPERTIES DEFINE_SYMBOL ${NAME_UPPER}_EXPORTS)

    set_target_properties(${target} PROPERTIES EXPORT_NAME E2D::${module})

    if(BUILD_SHARED_LIBS AND NOT THIS_STATIC)
        if(E2D_OS_WINDOWS)
            set_target_properties(${target} PROPERTIES DEBUG_POSTFIX -d)
            set_target_properties(${target} PROPERTIES SUFFIX "-${PROJECT_VERSION_MAJOR}${CMAKE_SHARED_LIBRARY_SUFFIX}")

            if(E2D_COMPILER_GCC OR E2D_COMPILER_CLANG)
                set_target_properties(${target} PROPERTIES PREFIX "")
                set_target_properties(${target} PROPERTIES IMPORT_SUFFIX ".a")
            endif()
        else()
            set_target_properties(${target} PROPERTIES DEBUG_POSTFIX -d)
        endif()
    else()
        set_target_properties(${target} PROPERTIES DEBUG_POSTFIX -s-d)
        set_target_properties(${target} PROPERTIES RELEASE_POSTFIX -s)
        set_target_properties(${target} PROPERTIES MINSIZEREL_POSTFIX -s)
        set_target_properties(${target} PROPERTIES RELWITHDEBINFO_POSTFIX -s)
    endif()

    set_target_properties(${target} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
    set_target_properties(${target} PROPERTIES VERSION ${PROJECT_VERSION})

    target_include_directories(${target}
            PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
            PRIVATE ${PROJECT_SOURCE_DIR}/src)

    if(NOT BUILD_SHARED_LIBS)
        target_compile_definitions(${target} PUBLIC "E2D_STATIC")
    endif()
endmacro()

macro(e2d_add_example target)
    cmake_parse_arguments(THIS "" "" "SOURCES;DEPENDS" ${ARGN})
    if(NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments when calling e2d_add_example: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    set(target_input ${THIS_SOURCES})
    add_executable(${target} ${target_input})

    set_target_properties(${target} PROPERTIES DEBUG_POSTFIX -d)

    if(THIS_DEPENDS)
        target_link_libraries(${target} PRIVATE ${THIS_DEPENDS})
    endif()
endmacro()