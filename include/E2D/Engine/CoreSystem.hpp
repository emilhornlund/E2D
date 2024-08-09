/**
 * @file CoreSystem.hpp
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

#ifndef E2D_ENGINE_CORE_SYSTEM_HPP
#define E2D_ENGINE_CORE_SYSTEM_HPP

#include <E2D/Engine/System.hpp>

namespace e2d
{

/**
 * @class CoreSystem
 * @ingroup engine
 * @brief Manages the initialization and shutdown of core SDL subsystems.
 *
 * The CoreSystem class is responsible for initializing and shutting down the
 * essential SDL subsystems that are required for the engine to function. This
 * includes systems like SDL timers and events, which are fundamental to the
 * engine's operation.
 */
class E2D_ENGINE_API CoreSystem final : public System
{
public:
    /**
     * @brief Constructs a new CoreSystem object.
     *
     * Initializes a new instance of the CoreSystem class. This constructor
     * sets up the initial state for the core system but does not initialize
     * any SDL subsystems.
     */
    CoreSystem();

    /**
     * @brief Destructor.
     *
     * Ensures proper cleanup of resources upon destruction. The destructor
     * will handle any necessary cleanup if the system has not been shut down
     * explicitly.
     */
    ~CoreSystem() final;

    /**
     * @brief Initializes the core SDL subsystems.
     *
     * Initializes essential SDL subsystems such as timers and events. This
     * method must be called before using any SDL functionality that depends
     * on these subsystems.
     *
     * @return True if all subsystems were successfully initialized, false otherwise.
     */
    bool initialize() final;

    /**
     * @brief Shuts down the core SDL subsystems.
     *
     * Properly shuts down the SDL subsystems that were initialized by this
     * system, ensuring that all resources are released and cleaned up.
     */
    void shutdown() final;

}; // class CoreSystem

} // namespace e2d

#endif //E2D_ENGINE_CORE_SYSTEM_HPP
