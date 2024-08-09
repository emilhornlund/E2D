/**
 * @file FontSystem.hpp
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

#ifndef E2D_ENGINE_FONT_SYSTEM_HPP
#define E2D_ENGINE_FONT_SYSTEM_HPP

#include <E2D/Engine/System.hpp>

namespace e2d
{

/**
 * @class FontSystem
 * @ingroup engine
 * @brief Manages the initialization and shutdown of the SDL TTF subsystem.
 *
 * The FontSystem class is responsible for initializing and shutting down the
 * SDL TTF (TrueType Font) subsystem, which is used for rendering text in
 * different fonts within the engine. This system is essential for any text
 * rendering operations.
 */
class E2D_ENGINE_API FontSystem final : public System
{
public:
    /**
     * @brief Constructs a new FontSystem object.
     *
     * Initializes a new instance of the FontSystem class. This constructor
     * sets up the initial state for the font system but does not initialize
     * the SDL TTF subsystem.
     */
    FontSystem();

    /**
     * @brief Destructor.
     *
     * Ensures proper cleanup of resources upon destruction. The destructor
     * will handle any necessary cleanup if the system has not been shut down
     * explicitly.
     */
    ~FontSystem() final;

    /**
     * @brief Initializes the SDL TTF subsystem.
     *
     * Initializes the SDL TTF subsystem, which is required for loading and
     * rendering TrueType fonts. This method must be called before any text
     * rendering can occur.
     *
     * @return True if the subsystem was successfully initialized, false otherwise.
     */
    bool initialize() final;

    /**
     * @brief Shuts down the SDL TTF subsystem.
     *
     * Properly shuts down the SDL TTF subsystem, ensuring that all resources
     * related to font rendering are released and cleaned up.
     */
    void shutdown() final;

}; // class FontSystem

} // namespace e2d

#endif //E2D_ENGINE_FONT_SYSTEM_HPP
