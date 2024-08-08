/**
 * Config.hpp
 *
 * MIT License
 *
 * Copyright (c) 2024 Emil Hörnlund
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
#if defined(_WIN32)
#define E2D_SYSTEM_WINDOWS

#ifndef NOMINMAX
#define NOMINMAX
#endif
#elif defined(__unix__)
#if defined(__linux__)
// Linux
#define E2D_SYSTEM_LINUX
#else
// Unsupported UNIX system
#error This UNIX operating system is not supported by E2D library
#endif
#elif defined(__APPLE__) && defined(__MACH__)
#include "TargetConditionals.h"

#if TARGET_OS_MAC
// macOS
#define E2D_SYSTEM_MACOS
#else
// Unsupported Apple system
#error This Apple operating system is not supported by E2D library
#endif
#else
// Unsupported system
#error This operating system is not supported by E2D library
#endif

/**
 * Define a portable debug macro
 */
#ifndef NDEBUG
#define E2D_DEBUG
#endif

/**
 * Define helpers to create portable import / export macros for each module
 */
#if !defined(E2D_STATIC)
#if defined(E2D_SYSTEM_WINDOWS)
// Windows compilers need specific (and different) keywords for export and import
#define E2D_API_EXPORT __declspec(dllexport)
#define E2D_API_IMPORT __declspec(dllimport)

// For Visual C++ compilers, we also need to turn off this annoying C4251 warning
#ifdef _MSC_VER
#pragma warning(disable : 4251)
#endif
#else // Linux, FreeBSD, macOS
#define E2D_API_EXPORT __attribute__((__visibility__("default")))
#define E2D_API_IMPORT __attribute__((__visibility__("default")))
#endif

#else
// Static build doesn't need import/export macros
#define E2D_API_EXPORT
#define E2D_API_IMPORT
#endif

#endif //E2D_CONFIG_HPP
