/**
 * @file SystemManager.hpp
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

#ifndef E2D_CORE_SYSTEM_MANAGER_HPP
#define E2D_CORE_SYSTEM_MANAGER_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/NonCopyable.hpp>

#include <E2D/Engine/System.hpp>

#include <memory>
#include <stack>

namespace e2d
{

/**
 * @class SystemManager
 * @ingroup engine
 * @brief Manages the initialization and shutdown of engine subsystems.
 *
 * The SystemManager class is responsible for handling the lifecycle of various engine subsystems.
 * It ensures that systems are initialized and shut down in a controlled manner, maintaining the
 * correct order of operations. This class follows the singleton pattern, providing a single
 * point of management for all subsystems throughout the application.
 */
class E2D_ENGINE_API SystemManager final : NonCopyable
{
public:
    /**
     * @brief Retrieves the singleton instance of the SystemManager.
     *
     * Provides access to the single instance of the SystemManager. This ensures that only one
     * SystemManager exists, which centralizes the management of engine subsystems.
     *
     * @return A reference to the SystemManager singleton instance.
     */
    static SystemManager& getInstance();

    /**
     * @brief Initializes a specific subsystem.
     *
     * This template method initializes a subsystem of type `T`, which must derive from the
     * `System` base class. The subsystem is created, initialized, and then stored in a stack
     * for later shutdown. This method ensures that each system is only initialized once and
     * that dependencies between systems are respected.
     *
     * @tparam T The type of the subsystem to initialize. `T` must be derived from `System`.
     *
     * @return True if the subsystem was successfully initialized, false otherwise.
     */
    template <typename T>
    bool initialize();

    /**
     * @brief Shuts down all initialized subsystems.
     *
     * This method shuts down all subsystems in the reverse order of their initialization,
     * ensuring that dependencies are correctly handled during the shutdown process. Each
     * subsystem is popped from the stack and its `shutdown` method is called.
     */
    void shutdown();

private:
    /**
     * @brief Constructs a new SystemManager object.
     *
     * Initializes a new instance of the SystemManager class. This constructor is private
     * to enforce the singleton pattern, preventing the creation of multiple instances.
     */
    SystemManager();

    /**
     * @brief Destructor.
     *
     * Ensures proper cleanup of resources upon destruction. The destructor will be invoked
     * automatically when the singleton instance is destroyed.
     */
    ~SystemManager();

    std::stack<std::unique_ptr<System>> m_systems; //!< Stack to manage the order of subsystem initialization and shutdown.

}; // SystemManager class

} // namespace e2d

#include <E2D/Engine/SystemManager.inl>

#endif //E2D_CORE_SYSTEM_MANAGER_HPP
