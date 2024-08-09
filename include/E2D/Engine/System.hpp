/**
 * @file System.hpp
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

#ifndef E2D_ENGINE_SYSTEM_HPP
#define E2D_ENGINE_SYSTEM_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/NonCopyable.hpp>

namespace e2d
{

/**
 * @class System
 * @ingroup engine
 * @brief Abstract base class for all engine subsystems.
 *
 * The System class serves as the abstract base class for all engine subsystems.
 * It defines a standard interface for initialization and shutdown operations
 * that must be implemented by all derived subsystems. This ensures that each
 * subsystem follows a consistent lifecycle, making it easier to manage and
 * integrate into the engine as a whole.
 */
class E2D_ENGINE_API System : NonCopyable
{
public:
    /**
     * @brief Constructs a new System object.
     *
     * Initializes a new instance of the System class. This constructor is protected
     * to ensure that the System class cannot be instantiated directly, but only
     * through derived classes.
     */
    System();

    /**
     * @brief Pure virtual destructor.
     *
     * Ensures proper cleanup of resources upon destruction. Being a pure virtual destructor,
     * it enforces that derived classes must implement their own destructors to handle
     * resource cleanup appropriately.
     */
    virtual ~System() = 0;

    /**
     * @brief Initializes the subsystem.
     *
     * This pure virtual method must be implemented by all derived classes. It is responsible
     * for setting up the subsystem, allocating resources, and ensuring that it is ready
     * for use. This method is called by the SystemManager during the engine's initialization phase.
     *
     * @return True if initialization is successful, false otherwise.
     */
    virtual bool initialize() = 0;

    /**
     * @brief Shuts down the subsystem.
     *
     * This pure virtual method must be implemented by all derived classes. It is responsible
     * for properly releasing resources and performing any necessary cleanup. This method is
     * called by the SystemManager during the engine's shutdown phase.
     */
    virtual void shutdown() = 0;

}; // class System

} // namespace e2d

#endif //E2D_ENGINE_SYSTEM_HPP
