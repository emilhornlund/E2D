/**
 * @file Window.hpp
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

#ifndef E2D_ENGINE_WINDOW_HPP
#define E2D_ENGINE_WINDOW_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/Color.hpp>
#include <E2D/Core/NonCopyable.hpp>

#include <memory>
#include <string>

struct SDL_Window; // Forward declaration of SDL_Window

namespace e2d::internal
{

/**
 * @class Window
 * @ingroup engine
 * @brief Represents a graphical window.
 *
 * This class provides functionalities to create, manage, and interact with a graphical window.
 * It abstracts the underlying implementation details and provides a simple interface for window management.
 */
class E2D_ENGINE_API Window final : NonCopyable
{
public:
    /**
     * @brief Constructs a new Window object.
     *
     * Initializes a new Window object.
     */
    Window();

    /**
     * @brief Destructor.
     *
     * Ensures proper cleanup of resources upon destruction.
     */
    ~Window();

    /**
     * @brief Creates a window with the specified properties.
     *
     * Initializes the window with a title, width, and height.
     *
     * @param title The title of the window.
     * @param width The width of the window in pixels.
     * @param height The height of the window in pixels.
     * @return True if the creation was successful, false otherwise.
     */
    bool create(const char* title, int width, int height);

    /**
     * @brief Checks if the window is created and valid.
     *
     * Determines whether the window is currently created and valid for use.
     *
     * @return True if the window is created, false otherwise.
     */
    [[maybe_unused]] bool isCreated() const;

    /**
     * @brief Destroys the window, freeing its resources.
     *
     * Frees the resources associated with the window.
     */
    void destroy();

    /**
     * @brief Retrieves the native window object.
     *
     * Provides access to the underlying SDL_Window object used for managing the window.
     *
     * @return A pointer to the underlying SDL_Window object.
     */
    SDL_Window* getNativeWindow() const;

private:
    SDL_Window* m_window{nullptr}; //!< Pointer to the underlying SDL_Window object.

}; // class Window

} // namespace e2d::internal

#endif //E2D_ENGINE_WINDOW_HPP
