/**
 * Application.hpp
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

#ifndef E2D_ENGINE_APPLICATION_HPP
#define E2D_ENGINE_APPLICATION_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/Color.hpp>
#include <E2D/Core/NonCopyable.hpp>

#include <memory>
#include <string>

/**
 * @brief Namespace for E2D
 */
namespace e2d
{
class Renderer; // Forward declaration of Renderer
class Window;   // Forward declaration of Window

/**
 * @brief Represents the application class.
 */
class E2D_ENGINE_API Application : NonCopyable
{
public:
    /**
     * @brief Constructs an Application object.
     *
     * @param windowTitle The windowTitle of the window
     */
    explicit Application(std::string windowTitle);

    /**
     * @brief Virtual destructor for Application.
     */
    virtual ~Application() = 0;

    /**
     * @brief Runs the application.
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
     * @param exitCode The exit code of the application (default is 0).
     */
    void quit(int exitCode = 0);

protected:
    /**
     * @brief Get the background color of the window
     *
     * @return The background color
     */
    [[nodiscard]] const Color& getBackgroundColor() const;

    /**
     * @brief Set the background color of the window
     *
     * @param backgroundColor The background color
     */
    void setBackgroundColor(const Color& backgroundColor);

private:
    int                       m_exitCode = 0;     //!< The exit code of the application.
    bool                      m_running  = false; //!< Flag indicating whether the application is running.
    const std::string         m_windowTitle;      //!< The title of the window.
    std::unique_ptr<Window>   m_window;           //!< Unique pointer to the window
    std::unique_ptr<Renderer> m_renderer;         //!< Unique pointer to the renderer
    Color                     m_backgroundColor;  //!< The background color of the window

    /**
     * @brief Handles SDL events such as window close event.
     */
    void handleEvents();

}; //Application class

} // namespace e2d

#endif //E2D_ENGINE_APPLICATION_HPP
