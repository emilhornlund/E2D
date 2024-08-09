/**
 * @file Application.hpp
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

#ifndef E2D_ENGINE_APPLICATION_HPP
#define E2D_ENGINE_APPLICATION_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/Color.hpp>
#include <E2D/Core/NonCopyable.hpp>

#include <memory>
#include <string>

namespace e2d
{
class ObjectRegistry;   // Forward declaration of ObjectRegistry
class ResourceRegistry; // Forward declaration of ResourceRegistry

/**
 * @class Application
 * @ingroup engine
 * @brief Abstract base for managing the lifecycle and main loop of the application.
 *
 * The Application class is responsible for initializing the game, handling the main loop,
 * processing events, updating the game state, and rendering frames. It serves as the entry point
 * for the E2D engine and orchestrates the overall flow of the game.
 */
class E2D_ENGINE_API Application : NonCopyable
{
public:
    /**
     * @brief Constructs a new Application.
     *
     * Initializes a new instance of the Application class with the specified window title.
     *
     * @param windowTitle The title of the window.
     */
    explicit Application(std::string windowTitle);

    /**
     * @brief Pure virtual destructor.
     *
     * Ensures proper cleanup of resources upon destruction.
     */
    virtual ~Application() = 0;

    /**
     * @brief Runs the application.
     *
     * Starts the main loop of the application and continues running until the application quits.
     *
     * @return The exit code of the application.
     */
    int run();

    /**
     * @brief Checks if the application is running.
     *
     * @return True if the application is running, false otherwise.
     */
    [[maybe_unused]] bool isRunning() const;

    /**
     * @brief Quits the application.
     *
     * Signals the application to stop running and sets the exit code.
     *
     * @param exitCode The exit code of the application (default is 0).
     */
    void quit(int exitCode = 0);

    /**
     * @brief Gets the ObjectRegistry instance used by the application.
     *
     * Provides access to the object registry managed by the application.
     *
     * @return A reference to the ObjectRegistry.
     */
    ObjectRegistry& getObjectRegistry() const;

    /**
     * @brief Gets the ResourceRegistry instance used by the application.
     *
     * Provides access to the resource registry managed by the application.
     *
     * @return A reference to the ResourceRegistry.
     */
    ResourceRegistry& getResourceRegistry() const;

    /**
     * @brief Gets the background color of the window.
     *
     * Retrieves the current background color of the window.
     *
     * @return The background color.
     */
    [[nodiscard]] const Color& getBackgroundColor() const;

    /**
     * @brief Sets the background color of the window.
     *
     * Changes the background color of the window to the specified color.
     *
     * @param backgroundColor The new background color.
     */
    void setBackgroundColor(const Color& backgroundColor);

protected:
    /**
     * @brief Called when the application starts running.
     *
     * Override this method in derived classes to implement custom logic that should
     * occur when the application begins running.
     */
    virtual void onRunning();

private:
    int                               m_exitCode = 0;     //!< The exit code of the application.
    bool                              m_running  = false; //!< Flag indicating whether the application is running.
    const std::string                 m_windowTitle;      //!< The title of the window.
    std::unique_ptr<ObjectRegistry>   m_objectRegistry;   //!< Unique pointer to the object registry.
    std::unique_ptr<ResourceRegistry> m_resourceRegistry; //!< Unique pointer to the resource registry.
    Color                             m_backgroundColor;  //!< The background color of the window.

}; // class Application

} // namespace e2d

#endif //E2D_ENGINE_APPLICATION_HPP
