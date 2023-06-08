#
# Try to find SDL2_ttf libraries and include paths.
# Once done this will define
#
# SDL2_TTF_INCLUDE_DIR
# SDL2_TTF_LIBRARY
#

if(NOT SDL2_DIR)
    set(SDL2_DIR "" CACHE PATH "SDL2 directory")
endif()

if(NOT SDL2_TTF_INCLUDE_DIR AND SDL2TTF_INCLUDE_DIR)
    set(SDL2_TTF_INCLUDE_DIR ${SDL2TTF_INCLUDE_DIR} CACHE PATH "directory cache entry initialized from old variable name")
endif()

find_path(SDL2_TTF_INCLUDE_DIR SDL_ttf.h
    HINTS
        ENV SDL2TTFDIR
        ${SDL2_TTF_DIR}
        ENV SDL2DIR
        ${SDL2_DIR}
    PATH_SUFFIXES SDL2
        # path suffixes to search inside ENV{SDL2DIR}
        include/SDL2 include
)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(VC_LIB_PATH_SUFFIX lib/x64)
else()
    set(VC_LIB_PATH_SUFFIX lib/x86)
endif()

if(NOT SDL2_TTF_LIBRARY AND SDL2TTF_LIBRARY)
    set(SDL2_TTF_LIBRARY ${SDL2TTF_LIBRARY} CACHE FILEPATH "file cache entry initialized from old variable name")
endif()

find_library(SDL2_TTF_LIBRARY
    NAMES SDL2_ttf
    HINTS
        ENV SDL2TTFDIR
        ENV SDL2DIR
        ${SDL2_DIR}
    PATH_SUFFIXES lib ${VC_LIB_PATH_SUFFIX}
)

if(SDL2_TTF_INCLUDE_DIR AND EXISTS "${SDL2_TTF_INCLUDE_DIR}/SDL_ttf.h")
    file(STRINGS "${SDL2_TTF_INCLUDE_DIR}/SDL_ttf.h" SDL2_TTF_VERSION_MAJOR_LINE REGEX "^#define[ \t]+SDL_TTF_MAJOR_VERSION[ \t]+[0-9]+$")
    file(STRINGS "${SDL2_TTF_INCLUDE_DIR}/SDL_ttf.h" SDL2_TTF_VERSION_MINOR_LINE REGEX "^#define[ \t]+SDL_TTF_MINOR_VERSION[ \t]+[0-9]+$")
    file(STRINGS "${SDL2_TTF_INCLUDE_DIR}/SDL_ttf.h" SDL2_TTF_VERSION_PATCH_LINE REGEX "^#define[ \t]+SDL_TTF_PATCHLEVEL[ \t]+[0-9]+$")
    string(REGEX REPLACE "^#define[ \t]+SDL_TTF_MAJOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL2_TTF_VERSION_MAJOR "${SDL2_TTF_VERSION_MAJOR_LINE}")
    string(REGEX REPLACE "^#define[ \t]+SDL_TTF_MINOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL2_TTF_VERSION_MINOR "${SDL2_TTF_VERSION_MINOR_LINE}")
    string(REGEX REPLACE "^#define[ \t]+SDL_TTF_PATCHLEVEL[ \t]+([0-9]+)$" "\\1" SDL2_TTF_VERSION_PATCH "${SDL2_TTF_VERSION_PATCH_LINE}")
    set(SDL2_TTF_VERSION_STRING ${SDL2_TTF_VERSION_MAJOR}.${SDL2_TTF_VERSION_MINOR}.${SDL2_TTF_VERSION_PATCH})
    unset(SDL2_TTF_VERSION_MAJOR_LINE)
    unset(SDL2_TTF_VERSION_MINOR_LINE)
    unset(SDL2_TTF_VERSION_PATCH_LINE)
    unset(SDL2_TTF_VERSION_MAJOR)
    unset(SDL2_TTF_VERSION_MINOR)
    unset(SDL2_TTF_VERSION_PATCH)
endif()

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(SDL2_TTF
        REQUIRED_VARS SDL2_TTF_LIBRARY SDL2_TTF_INCLUDE_DIR
        VERSION_VAR SDL2_TTF_VERSION_STRING)
