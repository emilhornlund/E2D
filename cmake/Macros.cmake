# this little macro lets you set any Xcode specific property
macro (e2d_set_xcode_property TARGET_NAME XCODE_PROPERTY XCODE_VALUE)
    set_property(TARGET ${TARGET_NAME} PROPERTY XCODE_ATTRIBUTE_${XCODE_PROPERTY} ${XCODE_VALUE})
endmacro()

# set the appropriate standard library on each platform for the given target
# example: sfml_set_stdlib(sfml-system)
macro(e2d_set_stdlib TARGET_NAME)
    if (E2D_OS_MACOSX AND E2D_COMPILER_CLANG)
        if (${CMAKE_GENERATOR} MATCHES "Xcode")
            e2d_set_xcode_property(${TARGET_NAME} CLANG_CXX_LIBRARY "libc++")
        else()
            target_compile_options(${TARGET_NAME} PRIVATE "-stdlib=libc++")
            target_link_libraries(${TARGET_NAME} PRIVATE "-stdlib=libc++")
        endif()
    endif()
endmacro()

macro(e2d_set_compiler_warnings TARGET_NAME)
    set(CLANG_WARNINGS
        -Werror
        -Wall
        -Wextra # reasonable and standard
        -Wshadow # warn the user if a variable declaration shadows one from a parent context
        -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual destructor. This helps
        # catch hard to track down memory errors
        -Wold-style-cast # warn for c-style casts
        -Wcast-align # warn for potential performance problem casts
        -Wunused # warn on anything being unused
        -Woverloaded-virtual # warn if you overload (not override) a virtual function
        -Wpedantic # warn if non-standard C++ is used
        -Wconversion # warn on type conversions that may lose data
        -Wsign-conversion # warn on sign conversions
        -Wnull-dereference # warn if a null dereference is detected
        -Wdouble-promotion # warn if float is implicit promoted to double
        -Wformat=2 # warn on security issues around functions that format output (ie printf)
    )

    set(GCC_WARNINGS
        ${CLANG_WARNINGS}
        -Wmisleading-indentation # warn if indentation implies blocks where blocks do not exist
        -Wduplicated-cond # warn if if / else chain has duplicated conditions
        -Wduplicated-branches # warn if if / else branches have duplicated code
        -Wlogical-op # warn about logical operations being used where bitwise were probably wanted
        -Wuseless-cast # warn if you perform a cast to the same type
    )

    if(E2D_COMPILER_CLANG)
        set(PROJECT_WARNINGS ${CLANG_WARNINGS})
    elseif(E2D_COMPILER_GCC)
        set(PROJECT_WARNINGS ${GCC_WARNINGS})
    endif()

    target_compile_options(${TARGET_NAME} INTERFACE ${PROJECT_WARNINGS})
endmacro()

macro(e2d_set_sanitizers TARGET_NAME)
    if(E2D_COMPILER_CLANG OR E2D_COMPILER_GCC)
        if(E2D_ENABLE_COVERAGE)
            target_compile_options(${TARGET_NAME} INTERFACE --coverage -O0 -g)
            target_link_libraries(${TARGET_NAME} INTERFACE --coverage)
        endif()
    endif()
endmacro()

macro(e2d_add_library TARGET_NAME)
    message(STATUS "Configuring ${TARGET_NAME}")

    # parse the arguments
    cmake_parse_arguments(THIS "" "" "SOURCES;DEPENDS" ${ARGN})
    if(NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments when calling e2d_add_library: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    # set a source group for the source files
    source_group("" FILES ${THIS_SOURCES})

    # create the target
    if(BUILD_SHARED_LIBS)
        add_library(${TARGET_NAME} ${THIS_SOURCES})
    else()
        add_library(${TARGET_NAME} STATIC ${THIS_SOURCES})
    endif()

    # determine c++ linker language
    set_target_properties(${TARGET_NAME} PROPERTIES LINKER_LANGUAGE CXX)

    # define the export symbol of the module
    string(REPLACE "-" "_" NAME_UPPER "${TARGET_NAME}")
    string(TOUPPER "${NAME_UPPER}" NAME_UPPER)
    set_target_properties(${TARGET_NAME} PROPERTIES COMPILE_FLAGS -D${NAME_UPPER}_EXPORTS)

    # adjust the output file prefix/suffix to match our conventions
    if(BUILD_SHARED_LIBS)
        set_target_properties(${TARGET_NAME} PROPERTIES DEBUG_POSTFIX -d)
    else()
        set_target_properties(${TARGET_NAME} PROPERTIES DEBUG_POSTFIX -s-d)
        set_target_properties(${TARGET_NAME} PROPERTIES RELEASE_POSTFIX -s)
        set_target_properties(${TARGET_NAME} PROPERTIES MINSIZEREL_POSTFIX -s)
        set_target_properties(${TARGET_NAME} PROPERTIES RELWITHDEBINFO_POSTFIX -s)
    endif()

    # set the version and soversion of the target (for compatible systems -- mostly Linuxes)
    set_target_properties(${TARGET_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
    set_target_properties(${TARGET_NAME} PROPERTIES VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})

    # set the target's folder for IDEs that support it
    set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "E2D")

    # set the target flags to use the appropriate C++ standard library
    e2d_set_stdlib(${TARGET_NAME})

    # set compiler warning flags for the target
    e2d_set_compiler_warnings(${TARGET_NAME})

    # set sanitizer options if supported by compiler
    e2d_set_sanitizers(${TARGET_NAME})

    # build frameworks or dylibs
    if(E2D_OS_MACOSX AND BUILD_SHARED_LIBS)
        if(E2D_BUILD_FRAMEWORKS)
            # adapt target to build frameworks instead of dylibs
            set_target_properties(${TARGET_NAME} PROPERTIES
                    FRAMEWORK TRUE
                    FRAMEWORK_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}
                    MACOSX_FRAMEWORK_IDENTIFIER com.emilhornlund.${TARGET_NAME}
                    MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}
                    MACOSX_FRAMEWORK_BUNDLE_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
        endif()

        # adapt install directory to allow distributing dylibs/frameworks in user's frameworks/application bundle
        # but only if cmake rpath options aren't set
        if(NOT CMAKE_SKIP_RPATH AND NOT CMAKE_SKIP_INSTALL_RPATH AND NOT CMAKE_INSTALL_RPATH AND NOT CMAKE_INSTALL_RPATH_USE_LINK_PATH AND NOT CMAKE_INSTALL_NAME_DIR)
            set_target_properties(${TARGET_NAME} PROPERTIES INSTALL_NAME_DIR "@rpath")
            if(NOT CMAKE_SKIP_BUILD_RPATH)
                set_target_properties(${TARGET_NAME} PROPERTIES BUILD_WITH_INSTALL_NAME_DIR TRUE)
            endif()
        endif()
    endif()

    # add the install rule
    install(TARGETS ${TARGET_NAME} EXPORT E2DConfigExport
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT bin
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT bin
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT devel
        FRAMEWORK DESTINATION "." COMPONENT bin
    )

    # add <project>/include
    target_include_directories(${TARGET_NAME}
        PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        PRIVATE ${PROJECT_SOURCE_DIR}/src
    )

    if (E2D_BUILD_FRAMEWORKS)
        target_include_directories(${TARGET_NAME} INTERFACE $<INSTALL_INTERFACE:E2D.framework>)
    else()
        target_include_directories(${TARGET_NAME} INTERFACE $<INSTALL_INTERFACE:include>)
    endif()

    # link the target to its E2D dependencies
    if(THIS_DEPENDS)
        target_link_libraries(${TARGET_NAME} PUBLIC ${THIS_DEPENDS})
    endif()

    # define E2D_STATIC if the build type is not set to 'shared'
    if(NOT E2D_BUILD_SHARED_LIBS)
        target_compile_definitions(${TARGET_NAME} PUBLIC "E2D_STATIC")
    endif()
endmacro()

macro(e2d_add_example TARGET_NAME)
    message(STATUS "Configuring ${TARGET_NAME}")

    # parse the arguments
    cmake_parse_arguments(THIS "" "INCLUDE" "SOURCES;DEPENDS" ${ARGN})
    if(NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments when calling e2d_add_example: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    # check for sources
    if(NOT THIS_SOURCES)
        message(FATAL_ERROR "No sources were given to target '${TARGET_NAME}'.")
    endif()

    # set a source group for the source files
    source_group("" FILES ${THIS_SOURCES})

    # create the target
    if(E2D_OS_MACOSX)
        add_executable(${TARGET_NAME} MACOSX_BUNDLE ${THIS_SOURCES})
    else()
        add_executable(${TARGET_NAME} ${THIS_SOURCES})
    endif()

    # set the debug suffix
    set_target_properties(${TARGET_NAME} PROPERTIES DEBUG_POSTFIX -d)

    # set the target's folder for IDEs that support it
    set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "Examples")

    # set the target flags to use the appropriate C++ standard library
    e2d_set_stdlib(${TARGET_NAME})

    # set compiler warning flags for the target
    e2d_set_compiler_warnings(${TARGET_NAME})

    if(THIS_INCLUDE)
        target_include_directories(${TARGET_NAME} PRIVATE ${THIS_INCLUDE})
    endif()

    # link the target to its E2D dependencies
    if(THIS_DEPENDS)
        target_link_libraries(${TARGET_NAME} PRIVATE ${THIS_DEPENDS})
    endif()
endmacro()

macro(e2d_add_test TARGET_NAME)
    message(STATUS "Configuring ${TARGET_NAME}")

    # parse the arguments
    cmake_parse_arguments(THIS "" "" "SOURCES;DEPENDS" ${ARGN})
    if(NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments when calling e2d_add_test: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    # set a source group for the source files
    source_group("" FILES ${THIS_SOURCES})

    # create the target
    add_executable(${TARGET_NAME} ${THIS_SOURCES})

    # set the target's folder (for IDEs that support it, e.g. Visual Studio)
    set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "Tests")

    target_include_directories(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

    # link the target to its E2D dependencies
    if(THIS_DEPENDS)
        target_link_libraries(${TARGET_NAME} PRIVATE ${THIS_DEPENDS})
    endif()

    # add the test
    add_test(${TARGET_NAME} ${TARGET_NAME})
endmacro()

macro(e2d_add_external TARGET_NAME)
    if(TARGET ${TARGET_NAME})
        message(FATAL_ERROR "Target '${TARGET_NAME}' is already defined")
    endif()

    cmake_parse_arguments(THIS "" "" "INCLUDE;LINK" ${ARGN})
    if (THIS_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Unknown arguments when calling e2d_add_external: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    add_library(${TARGET_NAME} INTERFACE)

    if (THIS_INCLUDE)
        foreach(include_dir IN LISTS THIS_INCLUDE)
            if (NOT include_dir)
                message(FATAL_ERROR "No path given for include dir ${THIS_INCLUDE}")
            endif()
            target_include_directories(${TARGET_NAME} INTERFACE "$<BUILD_INTERFACE:${include_dir}>")
        endforeach()
    endif()

    if (THIS_LINK)
        foreach(link_item IN LISTS THIS_LINK)
            if (NOT link_item)
                message(FATAL_ERROR "Missing item in ${THIS_LINK}")
            endif()
            target_link_libraries(${TARGET_NAME} INTERFACE "$<BUILD_INTERFACE:${link_item}>")
        endforeach()
    endif()

    install(TARGETS ${TARGET_NAME} EXPORT E2DConfigExport)
endmacro()

macro(e2d_find_package TARGET_NAME)
    if(TARGET ${TARGET_NAME})
        message(FATAL_ERROR "Target '${TARGET_NAME}' is already defined")
    endif()

    cmake_parse_arguments(THIS "" "" "INCLUDE;LINK" ${ARGN})
    if(THIS_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Unknown arguments when calling e2d_find_package: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules/")
    find_package(${TARGET_NAME} REQUIRED)

    set(INCLUDE_LIST "")
    if (THIS_INCLUDE)
        foreach(include_dir IN LISTS THIS_INCLUDE)
            list(APPEND INCLUDE_LIST "${${include_dir}}")
        endforeach()
    endif()

    set(LINK_LIST "")
    if (THIS_LINK)
        foreach(link_item IN LISTS THIS_LINK)
            list(APPEND LINK_LIST "${${link_item}}")
        endforeach()
    endif()

    e2d_add_external(${TARGET_NAME} INCLUDE ${INCLUDE_LIST} LINK ${LINK_LIST})
endmacro()

macro(e2d_export_targets)
    set(CURRENT_DIR "${PROJECT_SOURCE_DIR}/cmake")

    include(CMakePackageConfigHelpers)
    write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/E2DConfigVersion.cmake"
        VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}
        COMPATIBILITY SameMajorVersion
    )

    if (BUILD_SHARED_LIBS)
        set(config_name "Shared")
    else()
        set(config_name "Static")
    endif()
    set(targets_config_filename "E2D${config_name}Targets.cmake")

    export(EXPORT E2DConfigExport FILE "${CMAKE_CURRENT_BINARY_DIR}/${targets_config_filename}")

    if (E2D_BUILD_FRAMEWORKS)
        set(config_package_location "E2D.framework/Resources/CMake")
    else()
        set(config_package_location ${CMAKE_INSTALL_LIBDIR}/cmake/E2D)
    endif()

    configure_package_config_file(
        "${CURRENT_DIR}/E2DConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/E2DConfig.cmake"
        INSTALL_DESTINATION "${config_package_location}"
    )

    install(EXPORT E2DConfigExport FILE ${targets_config_filename} DESTINATION ${config_package_location})

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/E2DConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/E2DConfigVersion.cmake"
        DESTINATION ${config_package_location}
        COMPONENT devel
    )
endmacro()
