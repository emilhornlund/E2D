/**
 * @file Renderer.hpp
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

#ifndef E2D_ENGINE_RENDERER_HPP
#define E2D_ENGINE_RENDERER_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/Color.hpp>
#include <E2D/Core/NonCopyable.hpp>

#include <memory>

struct SDL_Renderer; // Forward declaration of SDL_Renderer

namespace e2d
{
class Renderable; // Forward declaration of Renderable
class Window;     // Forward declaration of Window

namespace internal
{
class RenderQueue; // Forward declaration of RenderQueue
} // namespace internal

/**
 * @class Renderer
 * @ingroup engine
 * @brief Handles the rendering process for graphical objects.
 *
 * The Renderer class is responsible for managing and executing the rendering process
 * of Renderable objects within the E2D Engine. It maintains a render queue to sort
 * and render objects based on their render priority. The Renderer class provides
 * functions for adding Renderable objects to the queue and for performing the actual
 * rendering process to display the content on the screen.
 */
class E2D_ENGINE_API Renderer final : NonCopyable
{
public:
    /**
     * @brief Constructs a new Renderer object.
     *
     * Initializes a new instance of the Renderer class.
     */
    Renderer();

    /**
     * @brief Destructor.
     *
     * Ensures proper cleanup of resources upon destruction.
     */
    ~Renderer();

    /**
     * @brief Initializes the renderer with the specified window.
     *
     * @param window A reference to the Window object to render to.
     * @return True if initialization is successful, false otherwise.
     */
    bool create(const Window& window);

    /**
     * @brief Checks if the renderer is created and valid.
     *
     * @return True if the renderer is created, false otherwise.
     */
    [[maybe_unused]] bool isCreated() const;

    /**
     * @brief Destroys the renderer, freeing its resources.
     */
    void destroy();

    /**
     * @brief Adds a Renderable object to the render queue.
     *
     * This method adds the given Renderable object to the render queue. The object
     * will be rendered in order based on its render priority when the render
     * method is called.
     *
     * @param renderable Pointer to the Renderable object to be added to the queue.
     */
    void draw(const Renderable* renderable);

    /**
     * @brief Renders content to the window using the specified color.
     *
     * Clears the screen with the specified color and renders the content.
     *
     * @param drawColor The color to clear the screen with before rendering.
     */
    void render(const Color& drawColor) const;

    /**
     * @brief Retrieves the native renderer object.
     *
     * Provides access to the underlying SDL_Renderer object.
     *
     * @return A pointer to the underlying SDL_Renderer object.
     */
    SDL_Renderer* getNativeRenderer() const;

private:
    SDL_Renderer*                          m_renderer{nullptr}; //!< Pointer to the underlying SDL_Renderer object.
    std::unique_ptr<internal::RenderQueue> m_renderQueue;       //!< Pointer to the render queue.

}; // class Renderer

} // namespace e2d

#endif //E2D_ENGINE_RENDERER_HPP
