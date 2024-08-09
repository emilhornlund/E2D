/**
 * @file GraphicsSystem.hpp
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

#ifndef E2D_ENGINE_GRAPHICS_SYSTEM_HPP
#define E2D_ENGINE_GRAPHICS_SYSTEM_HPP

#include <E2D/Engine/System.hpp>

namespace e2d
{

/**
 * @class GraphicsSystem
 * @ingroup engine
 * @brief Manages the initialization and shutdown of the SDL graphics subsystem.
 *
 * The GraphicsSystem class is responsible for initializing and shutting down
 * the SDL video subsystem and associated components, such as the SDL image
 * subsystem and the renderer. This system is essential for any rendering
 * operations in the engine.
 */
class E2D_ENGINE_API GraphicsSystem final : public System
{
public:
    /**
     * @brief Constructs a new GraphicsSystem object.
     *
     * Initializes a new instance of the GraphicsSystem class. This constructor
     * sets up the initial state for the graphics system but does not initialize
     * any SDL subsystems.
     */
    GraphicsSystem();

    /**
     * @brief Destructor.
     *
     * Ensures proper cleanup of resources upon destruction. The destructor
     * will handle any necessary cleanup if the system has not been shut down
     * explicitly.
     */
    ~GraphicsSystem() final;

    /**
     * @brief Initializes the SDL video and image subsystems.
     *
     * Initializes the SDL video subsystem, which is required for rendering
     * graphics, and the SDL image subsystem for handling various image formats.
     * Additionally, it initializes the renderer context used for drawing operations.
     *
     * @return True if all subsystems were successfully initialized, false otherwise.
     */
    bool initialize() final;

    /**
     * @brief Shuts down the SDL video and image subsystems.
     *
     * Properly shuts down the SDL video and image subsystems, along with the
     * renderer context, ensuring that all resources are released and cleaned up.
     */
    void shutdown() final;

}; // class GraphicsSystem

} // namespace e2d

#endif //E2D_ENGINE_GRAPHICS_SYSTEM_HPP
