if(E2D_OS_MACOS)
    set(ADDITIONAL_PATHS
            /Developer/Applications/Doxygen.app/Contents/Resources
            /Developer/Applications/Doxygen.app/Contents/MacOS
            $ENV{HOME}/Applications/Doxygen.app/Contents/Resources
            $ENV{HOME}/Applications/Doxygen.app/Contents/MacOS
            $ENV{HOME}/Applications/Developer/Doxygen.app/Contents/Resources
            $ENV{HOME}/Applications/Developer/Doxygen.app/Contents/MacOS)

    list(APPEND CMAKE_PROGRAM_PATH ${ADDITIONAL_PATHS})
endif()

find_package(Doxygen REQUIRED)

set(DOXYGEN_INPUT_DIR ${PROJECT_SOURCE_DIR})
set(DOXYGEN_OUTPUT_DIR ${PROJECT_BINARY_DIR}/docs)

if(E2D_OS_WINDOWS)
    find_program(DOXYGEN_HHC_PROGRAM
                 NAMES hhc.exe
                 PATHS "C:/Program Files/HTML Help Workshop" "C:/Program Files (x86)/HTML Help Workshop"
                 DOC "HTML Help Compiler program")
    if(DOXYGEN_HHC_PROGRAM)
        set(DOXYGEN_GENERATE_HTMLHELP YES)
    else()
        set(DOXYGEN_GENERATE_HTMLHELP NO)
    endif()
else()
    set(DOXYGEN_HHC_PROGRAM)
    set(DOXYGEN_GENERATE_HTMLHELP NO)
endif()

set(DOXYGEN_CONFIGURED_INPUT ${DOXYGEN_OUTPUT_DIR}/doxyfile)
configure_file(${DOXYGEN_INPUT_DIR}/docs/doxyfile.in ${DOXYGEN_CONFIGURED_INPUT} @ONLY)

add_custom_target(e2d-documentation
                  COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
                  COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIGURED_INPUT}
                  COMMAND ${CMAKE_COMMAND} -E echo "Done."
                  WORKING_DIRECTORY ${DOXYGEN_INPUT_DIR})

install(FILES ${DOXYGEN_OUTPUT_DIR}/E2D.tag
        DESTINATION ${CMAKE_INSTALL_DOCDIR}
        COMPONENT e2d-documentation)

install(DIRECTORY ${DOXYGEN_OUTPUT_DIR}/html
        DESTINATION ${CMAKE_INSTALL_DOCDIR}
        COMPONENT e2d-documentation)

if(DOXYGEN_HHC_PROGRAM)
    install(FILES ${DOXYGEN_OUTPUT_DIR}/e2d.chm
            DESTINATION ${CMAKE_INSTALL_DOCDIR}
            COMPONENT e2d-documentation)
endif()