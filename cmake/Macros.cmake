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

    if(E2D_OS_MACOS)
        e2d_set_xcode_property(${target} CLANG_CXX_LIBRARY "libc++")
    endif()
endfunction()

macro(e2d_add_library module)
    cmake_parse_arguments(THIS "STATIC" "" "SOURCES" ${ARGN})
    if(NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments when calling e2d_add_library: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    string(TOLOWER e2d-${module} target)
    if(NOT BUILD_SHARED_LIBS OR THIS_STATIC)
        add_library(${target} STATIC ${THIS_SOURCES})
    else()
        add_library(${target} ${THIS_SOURCES})
    endif()
    add_library(E2D::${module} ALIAS ${target})

    target_compile_features(${target} PUBLIC cxx_std_20)

    set_target_properties(${target} PROPERTIES LINKER_LANGUAGE CXX)

    e2d_set_target_warnings(${target})
    e2d_set_public_symbols_hidden(${target})

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

        if(BUILD_SHARED_LIBS AND NOT THIS_STATIC)
            set_target_properties(${target} PROPERTIES
                                  PDB_NAME "${target}${E2D_PDB_POSTFIX}"
                                  PDB_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
        else()
            set_target_properties(${target} PROPERTIES
                                  COMPILE_PDB_NAME "${target}-s${E2D_PDB_POSTFIX}"
                                  COMPILE_PDB_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
        endif()
    endif()

    if(E2D_OS_MACOS AND BUILD_SHARED_LIBS AND NOT THIS_STATIC)
        if(E2D_BUILD_FRAMEWORKS)
            set_target_properties(${target} PROPERTIES
                                  FRAMEWORK TRUE
                                  FRAMEWORK_VERSION ${PROJECT_VERSION}
                                  MACOSX_FRAMEWORK_IDENTIFIER com.emilhornlund.${target}
                                  MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${PROJECT_VERSION}
                                  MACOSX_FRAMEWORK_BUNDLE_VERSION ${PROJECT_VERSION})
        endif()

        if(NOT CMAKE_SKIP_RPATH AND NOT CMAKE_SKIP_INSTALL_RPATH AND NOT CMAKE_INSTALL_RPATH AND NOT CMAKE_INSTALL_RPATH_USE_LINK_PATH AND NOT CMAKE_INSTALL_NAME_DIR)
            set_target_properties(${target} PROPERTIES INSTALL_NAME_DIR "@rpath")
            if(NOT CMAKE_SKIP_BUILD_RPATH)
                set_target_properties(${target} PROPERTIES BUILD_WITH_INSTALL_NAME_DIR TRUE)
            endif()
        endif()
    endif()

    set_target_properties(${target} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
    set_target_properties(${target} PROPERTIES VERSION ${PROJECT_VERSION})

    install(TARGETS ${target} EXPORT E2DConfigExport
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT bin
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT bin
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT devel
            FRAMEWORK DESTINATION "." COMPONENT bin)

    target_include_directories(${target}
                               PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                               PRIVATE ${PROJECT_SOURCE_DIR}/src)

    if(E2D_BUILD_FRAMEWORKS)
        target_include_directories(${target} INTERFACE $<INSTALL_INTERFACE:E2D.framework>)
    else()
        target_include_directories(${target} INTERFACE $<INSTALL_INTERFACE:include>)
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

function(e2d_add_test target SOURCES DEPENDS)
    source_group("" FILES ${SOURCES})

    add_executable(${target} ${SOURCES})

    set_target_properties(${target} PROPERTIES FOLDER "Tests")

    target_link_libraries(${target} PRIVATE ${DEPENDS} Catch2::Catch2WithMain)

    e2d_set_target_warnings(${target})
    e2d_set_public_symbols_hidden(${target})

    catch_discover_tests(${target})
endfunction()

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

    install(TARGETS ${target} EXPORT E2DConfigExport)
endfunction()

function(e2d_export_targets)
    set(CURRENT_DIR "${PROJECT_SOURCE_DIR}/cmake")

    include(CMakePackageConfigHelpers)
    write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/E2DConfigVersion.cmake"
                                     VERSION ${PROJECT_VERSION}
                                     COMPATIBILITY SameMajorVersion)

    if(BUILD_SHARED_LIBS)
        set(config_name "Shared")
    else()
        set(config_name "Static")
    endif()
    set(targets_config_filename "E2D${config_name}Targets.cmake")

    export(EXPORT E2DConfigExport
           FILE "${CMAKE_CURRENT_BINARY_DIR}/${targets_config_filename}")

    if(E2D_BUILD_FRAMEWORKS)
        set(config_package_location "E2D.framework/Resources/CMake")
    else()
        set(config_package_location ${CMAKE_INSTALL_LIBDIR}/cmake/E2D)
    endif()

    configure_package_config_file("${CURRENT_DIR}/E2DConfig.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/E2DConfig.cmake"
                                  INSTALL_DESTINATION "${config_package_location}")
    configure_package_config_file("${CURRENT_DIR}/E2DConfigDependencies.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/E2DConfigDependencies.cmake"
                                  INSTALL_DESTINATION "${config_package_location}")

    install(EXPORT E2DConfigExport
            FILE ${targets_config_filename}
            DESTINATION ${config_package_location})

    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/E2DConfig.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/E2DConfigDependencies.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/E2DConfigVersion.cmake"
            DESTINATION ${config_package_location}
            COMPONENT devel)
endfunction()
