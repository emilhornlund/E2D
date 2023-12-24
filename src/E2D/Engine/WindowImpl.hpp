/**
* WindowImpl.hpp
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

#ifndef E2D_ENGINE_WINDOW_IMPL_HPP
#define E2D_ENGINE_WINDOW_IMPL_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/NonCopyable.hpp>

#include <memory>

struct SDL_Window; // Forward declaration of SDL_Window

/**
 * @brief Namespace for E2D internal
 */
namespace e2d::internal
{

/**
 * @class WindowImpl
 * @brief Internal implementation class for Window.
 *
 * This class manages the low-level details of window creation, management, and destruction.
 * It interfaces directly with the underlying windowing system.
 */
class E2D_ENGINE_API WindowImpl final : NonCopyable
{
public:
    /**
     * @brief Default constructor for WindowImpl.
     *
     * Initializes a new instance of the WindowImpl class.
     */
    WindowImpl();

    /**
     * @brief Destructor for WindowImpl.
     *
     * Cleans up resources used by the WindowImpl object.
     */
    ~WindowImpl();

    /**
     * @brief Creates a window with specified properties.
     *
     * @param title The title of the window.
     * @param width The width of the window in pixels.
     * @param height The height of the window in pixels.
     * @return True if the window is successfully created, false otherwise.
     */
    bool create(const char* title, int width, int height);

    /**
     * @brief Checks if the window is currently created and valid.
     *
     * @return True if the window is created, false otherwise.
     */
    [[maybe_unused]] bool isCreated() const;

    /**
     * @brief Destroys the window, freeing associated resources.
     */
    void destroy();

    /**
     * @brief Retrieves the native window object.
     *
     * @return A pointer to the underlying SDL_Window object.
     */
    SDL_Window* getWindow() const;

private:
    SDL_Window* m_window{nullptr}; //!< Pointer to the SDL_Window object.

}; // class WindowImpl

} // namespace e2d::internal

#endif //E2D_ENGINE_WINDOW_IMPL_HPP
