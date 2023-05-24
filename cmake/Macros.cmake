include(CMakeParseArguments)

include(${CMAKE_CURRENT_LIST_DIR}/CompilerWarnings.cmake)

function(e2d_set_public_symbols_hidden target)
    set_target_properties(${target} PROPERTIES
                          CXX_VISIBILITY_PRESET hidden
                          VISIBILITY_INLINES_HIDDEN YES)
endfunction()

macro(e2d_set_xcode_property TARGET XCODE_PROPERTY XCODE_VALUE)
    set_property (TARGET ${TARGET} PROPERTY XCODE_ATTRIBUTE_${XCODE_PROPERTY} ${XCODE_VALUE})
endmacro()

function(e2d_set_stdlib target)
    if(E2D_OS_WINDOWS AND E2D_COMPILER_GCC)
        if(E2D_USE_STATIC_STD_LIBS AND NOT E2D_COMPILER_GCC_TDM)
            target_link_libraries(${target} PRIVATE "-static-libgcc" "-static-libstdc++")
        elseif(NOT E2D_USE_STATIC_STD_LIBS AND E2D_COMPILER_GCC_TDM)
            target_link_libraries(${target} PRIVATE "-shared-libgcc" "-shared-libstdc++")
        endif()
    endif()

    if(E2D_OS_MACOSX)
        e2d_set_xcode_property(${target} CLANG_CXX_LIBRARY "libc++")
    endif()
endfunction()

macro(e2d_add_library module)
    cmake_parse_arguments(THIS "INTERFACE" "" "SOURCES" ${ARGN})
    if(NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments when calling e2d_add_library: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    string(TOLOWER e2d-${module} target)
    if(NOT BUILD_SHARED_LIBS)
        add_library(${target} STATIC ${THIS_SOURCES})
    elseif(THIS_INTERFACE)
        add_library(${target} INTERFACE)
        target_sources(${target} INTERFACE ${THIS_SOURCES})
    else()
        add_library(${target} ${THIS_SOURCES})
    endif()
    add_library(E2D::${module} ALIAS ${target})

    if(NOT THIS_INTERFACE)
        target_compile_features(${target} PUBLIC cxx_std_20)
    endif()

    set_target_properties(${target} PROPERTIES LINKER_LANGUAGE CXX)

    if(NOT THIS_INTERFACE)
        e2d_set_target_warnings(${target})
    endif()
    e2d_set_public_symbols_hidden(${target})

    string(REPLACE "-" "_" NAME_UPPER "${target}")
    string(TOUPPER "${NAME_UPPER}" NAME_UPPER)
    set_target_properties(${target} PROPERTIES DEFINE_SYMBOL ${NAME_UPPER}_EXPORTS)

    set_target_properties(${target} PROPERTIES EXPORT_NAME E2D::${module})

    if(BUILD_SHARED_LIBS)
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
        
        if(E2D_USE_STATIC_STD_LIBS)
            set_property(TARGET ${target} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
        endif()
    endif()

    e2d_set_stdlib(${target})

    if (E2D_GENERATE_PDB)
        if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
            set(E2D_PDB_POSTFIX "-d")
        else()
            set(E2D_PDB_POSTFIX "")
        endif()

        if(BUILD_SHARED_LIBS)
            set_target_properties(${target} PROPERTIES
                                  PDB_NAME "${target}${E2D_PDB_POSTFIX}"
                                  PDB_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
        else()
            set_target_properties(${target} PROPERTIES
                                  COMPILE_PDB_NAME "${target}-s${E2D_PDB_POSTFIX}"
                                  COMPILE_PDB_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
        endif()
    endif()

    set_target_properties(${target} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
    set_target_properties(${target} PROPERTIES VERSION ${PROJECT_VERSION})

    if(THIS_INTERFACE)
        target_include_directories(${target} INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
    else()
        target_include_directories(${target}
                PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                PRIVATE ${PROJECT_SOURCE_DIR}/src)
    endif()

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

    if(E2D_USE_STATIC_STD_LIBS)
        set_property(TARGET ${target} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    endif()

    e2d_set_target_warnings(${target})
    e2d_set_public_symbols_hidden(${target})

    set_target_properties(${target} PROPERTIES DEBUG_POSTFIX -d)

    e2d_set_stdlib(${target})

    if(THIS_DEPENDS)
        target_link_libraries(${target} PRIVATE ${THIS_DEPENDS})
    endif()
endmacro()

function(e2d_find_package)
    list(GET ARGN 0 target)
    list(REMOVE_AT ARGN 0)

    if(TARGET ${target})
        message(FATAL_ERROR "Target '${target}' is already defined")
    endif()

    cmake_parse_arguments(THIS "" "" "INCLUDE;LINK" ${ARGN})
    if(THIS_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Unknown arguments when calling e2d_find_package: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    find_package(${target} REQUIRED)
    add_library(${target} INTERFACE)

    foreach(include_dir IN LISTS THIS_INCLUDE)
        target_include_directories(${target} SYSTEM INTERFACE "$<BUILD_INTERFACE:${${include_dir}}>")
    endforeach()

    foreach(link_item IN LISTS THIS_LINK)
        target_link_libraries(${target} INTERFACE "$<BUILD_INTERFACE:${${link_item}}>")
    endforeach()
endfunction()