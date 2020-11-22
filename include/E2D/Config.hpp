/**
 * E2D
 * Copyright (C) 2020 (emil.hornlund@me.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef E2D_CONFIG_HPP
#define E2D_CONFIG_HPP

/**
 * Define the E2D version
 */
#define E2D_VERSION_MAJOR 1
#define E2D_VERSION_MINOR 0
#define E2D_VERSION_PATCH 0


/**
 * Identify the operating system
 * see https://sourceforge.net/p/predef/wiki/Home/
 */
#if defined(__APPLE__) && defined(__MACH__)

    // Apple platform, see which one it is
    #include "TargetConditionals.h"

    #if TARGET_OS_MAC

        // MacOS
        #define E2D_SYSTEM_MACOS

    #else

        // Unsupported Apple system
        #error This Apple operating system is not supported by E2D library

    #endif

#elif defined(__unix__)

    // UNIX system, see which one it is
    #if defined(__linux__)

        // Linux
        #define E2D_SYSTEM_LINUX

    #else

        // Unsupported UNIX system
        #error This UNIX operating system is not supported by E2D library

    #endif

#else

    // Unsupported system
    #error This operating system is not supported by E2D library

#endif


/**
 * Define a portable debug macro
 */
#if !defined(NDEBUG)

    #define E2D_DEBUG

#endif


/**
 * Define helpers to create portable import / export macros for each module
 */
#if !defined(E2D_STATIC)

    #if __GNUC__ >= 4

        // GCC 4 has special keywords for showing/hiding symbols,
        // the same keyword is used for both importing and exporting
        #define E2D_API_EXPORT __attribute__ ((__visibility__ ("default")))
        #define E2D_API_IMPORT __attribute__ ((__visibility__ ("default")))

    #else

        // GCC < 4 has no mechanism to explicitely hide symbols, everything's exported
        #define E2D_API_EXPORT
        #define E2D_API_IMPORT

    #endif

#else

    // Static build doesn't need import/export macros
    #define E2D_API_EXPORT
    #define E2D_API_IMPORT

#endif

#endif //E2D_CONFIG_HPP
