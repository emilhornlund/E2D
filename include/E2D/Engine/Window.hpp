/**
 * Window.hpp
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

#ifndef E2D_ENGINE_WINDOW_HPP
#define E2D_ENGINE_WINDOW_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/Color.hpp>
#include <E2D/Core/NonCopyable.hpp>

#include <memory>
#include <string>

struct SDL_Window;
struct SDL_Renderer;

struct SDLDestroyer
{
    void operator()(SDL_Window* window) const;
    void operator()(SDL_Renderer* renderer) const;
};

using WindowPtr   = std::unique_ptr<SDL_Window, SDLDestroyer>;
using RendererPtr = std::unique_ptr<SDL_Renderer, SDLDestroyer>;

/**
 * @brief Namespace for E2D
 */
namespace e2d
{

/**
 * @brief Represents a window and renderer.
 *
 * The Window class provides a wrapper around a window and renderer.
 * It manages the lifetime of these resources using smart pointers.
 */
class E2D_ENGINE_API Window final : NonCopyable
{
public:
    /**
     * @brief Default constructor.
     *
     * Constructs a Window object.
     */
    Window();

    /**
     * @brief Destructor.
     *
     * Destroys the Window object.
     */
    ~Window();

    /**
     * @brief Creates a window and renderer.
     *
     * Creates a window and renderer with the specified title.
     *
     * @param title The title of the window.
     * @return True if the creation was successful, false otherwise.
     */
    bool create(const std::string& title);

    /**
     * @brief Closes the window and renderer.
     *
     * Releases the ownership of the window and renderer resources.
     * The destruction of the resources is handled automatically by the smart pointers.
     */
    void close();

    /**
     * @brief Clears the renderer with a color.
     *
     * Clears the renderer with the specified color.
     *
     * @param color The color to clear the renderer with.
     */
    [[maybe_unused]] bool isOpened() const;

    /**
     * @brief Clears the renderer with a color.
     *
     * Clears the renderer with the specified color.
     *
     * @param color The color to clear the renderer with.
     */
    void clear(const Color& color);

    /**
     * @brief Presents the renderer.
     *
     * Presents the renderer, displaying the rendered content on the window.
     */
    void display();

private:
    WindowPtr   m_window;   //!< Pointer to the SDL window.
    RendererPtr m_renderer; //!< Pointer to the SDL renderer.
};

} // namespace e2d

#endif //E2D_ENGINE_WINDOW_HPP
