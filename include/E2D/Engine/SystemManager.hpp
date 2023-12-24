/**
* SystemManager.hpp
*
* MIT License
*
* Copyright (c) 2023 Emil Hörnlund
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

#ifndef E2D_ENGINE_SYSTEM_MANAGER_HPP
#define E2D_ENGINE_SYSTEM_MANAGER_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/NonCopyable.hpp>

#include <E2D/Engine/System.hpp>

#include <memory>
#include <vector>

/**
 * @brief Namespace for E2D
 */
namespace e2d
{
class System;

/**
 * @class SystemManager
 * @brief Manages the initialization and shutdown of all systems in the E2D Engine.
 *
 * SystemManager is a singleton class responsible for managing the lifecycle of all systems (like graphics, audio, etc.) in the E2D Engine.
 */
class E2D_ENGINE_API SystemManager final : NonCopyable
{
public:
    /**
     * @brief Retrieves the singleton instance of SystemManager.
     *
     * @return SystemManager& Reference to the singleton instance of SystemManager.
     */
    static SystemManager& getInstance();

    /**
     * @brief Adds a new system to the SystemManager.
     *
     * Template function that creates and adds a new system of type T to the SystemManager.
     *
     * @tparam T The type of the system to be added. Must be derived from System.
     */
    template <class T>
    void addSystem();

    /**
     * @brief Initializes all added systems.
     *
     * Calls the initialize method on all systems managed by the SystemManager.
     *
     * @return bool Returns true if all systems are successfully initialized, false otherwise.
     */
    bool initializeAll();

    /**
     * @brief Shuts down all added systems.
     *
     * Calls the shutdown method on all systems managed by the SystemManager.
     */
    void shutdownAll();

private:
    std::vector<std::unique_ptr<System>> m_systems; //!< Vector of unique pointers to System objects.

    /**
     * @brief Default constructor for SystemManager.
     *
     * Constructs a SystemManager object.
     */
    SystemManager();

    /**
     * @brief Destructor for SystemManager.
     *
     * Destroys the SystemManager object, releasing its resources and shutting down all managed systems.
     */
    ~SystemManager();

}; // class SystemManager

template <class T>
void SystemManager::addSystem()
{
    static_assert(std::is_base_of<System, T>::value, "T is not derived from System");
    this->m_systems.emplace_back(std::make_unique<T>());
}

} // namespace e2d

#endif //E2D_ENGINE_SYSTEM_MANAGER_HPP
