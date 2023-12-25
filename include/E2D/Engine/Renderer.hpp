/**
* Renderer.hpp
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

#ifndef E2D_ENGINE_RENDERER_HPP
#define E2D_ENGINE_RENDERER_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/Color.hpp>
#include <E2D/Core/NonCopyable.hpp>

#include <memory>

/**
 * @brief Namespace for E2D
 */
namespace e2d
{
class Window; // Forward declaration of Window

/**
 * @brief Namespace for E2D internal
 */
namespace internal
{
class RendererImpl; // Forward declaration of RendererImpl
}

/**
 * @class Renderer
 * @brief Represents a rendering context for drawing graphics.
 *
 * This class provides functionalities for rendering graphics onto a linked window.
 * It offers a simplified interface for drawing operations.
 */
class E2D_ENGINE_API Renderer final : NonCopyable
{
public:
    /**
     * @brief Default constructor for Renderer.
     *
     * Constructs a Renderer object.
     */
    Renderer();

    /**
     * @brief Destructor for Renderer.
     *
     * Destroys the Renderer object, releasing its resources.
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
     * @brief Renders content to the window using the specified color.
     *
     * @param drawColor The color to clear the screen with before rendering.
     */
    void render(const Color& drawColor) const;

    /**
     * @brief Retrieves a handle to the native renderer.
     *
     * This function is used internally to link the renderer with other components.
     *
     * @return A pointer to the native renderer handle.
     */
    void* getNativeRendererHandle() const;

private:
    std::unique_ptr<internal::RendererImpl> m_rendererImpl; //!< Pointer to the renderer implementation.

}; // class Renderer

} // namespace e2d

#endif //E2D_ENGINE_RENDERER_HPP
