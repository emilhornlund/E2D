/**
 * @file RendererContext.hpp
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

#ifndef E2D_ENGINE_RENDERER_CONTEXT_HPP
#define E2D_ENGINE_RENDERER_CONTEXT_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/NonCopyable.hpp>

#include <memory>

namespace e2d
{
class Renderer; // Forward declaration of Renderer
class Window;   // Forward declaration of Window
} // namespace e2d

namespace e2d::internal
{

/**
 * @class RendererContext
 * @ingroup engine
 * @brief @internal Manages the central context for rendering operations.
 *
 * The RendererContext class is a singleton responsible for managing and providing access to the
 * core rendering components, such as the window and the renderer. It ensures that the window and
 * renderer are properly initialized, accessed, and destroyed. This class encapsulates the
 * complexity of SDL's rendering setup and provides a simplified interface for other components
 * of the engine to interact with these resources.
 */
class E2D_ENGINE_API RendererContext final : NonCopyable
{
public:
    /**
     * @brief Retrieves the singleton instance of the RendererContext.
     *
     * Provides access to the single instance of the RendererContext. This method ensures that
     * only one instance of the RendererContext exists throughout the application.
     *
     * @return A reference to the RendererContext singleton instance.
     */
    static RendererContext& getInstance();

    /**
     * @brief Checks if the RendererContext is initialized.
     *
     * Determines whether the window and renderer have been successfully created and initialized.
     *
     * @return True if both the window and renderer are initialized, false otherwise.
     */
    bool isInitialized() const;

    /**
     * @brief Initializes the window and renderer.
     *
     * Creates the window and renderer necessary for rendering operations. This method must be
     * called before any rendering can take place. It sets up the window with a default title,
     * width, and height, and associates it with the renderer.
     *
     * @return True if initialization is successful, false otherwise.
     */
    bool initialize();

    /**
     * @brief Destroys the window and renderer.
     *
     * Properly cleans up and destroys the window and renderer managed by this context. This
     * method should be called during the shutdown process to release all associated resources.
     */
    void destroy();

    /**
     * @brief Gets the Window instance.
     *
     * Provides access to the window instance managed by the RendererContext. This method allows
     * other components of the engine to interact with the window.
     *
     * @return A reference to the Window.
     */
    Window& getWindow() const;

    /**
     * @brief Gets the Renderer instance.
     *
     * Provides access to the renderer instance managed by the RendererContext. The renderer is
     * used for drawing textures, shapes, and other graphical elements to the window.
     *
     * @return A reference to the Renderer.
     */
    Renderer& getRenderer() const;

private:
    /**
     * @brief Constructs a new RendererContext object.
     *
     * Initializes a new instance of the RendererContext class. This constructor is private
     * to enforce the singleton pattern, preventing the creation of multiple instances.
     */
    RendererContext();

    /**
     * @brief Destructor.
     *
     * Ensures proper cleanup of resources upon destruction. This destructor is responsible for
     * destroying the window and renderer if they are still initialized.
     */
    ~RendererContext();

    std::unique_ptr<Window>   m_window;   //!< Unique pointer to the window.
    std::unique_ptr<Renderer> m_renderer; //!< Unique pointer to the renderer.

}; // RendererContext class

} // namespace e2d::internal

#endif //E2D_ENGINE_RENDERER_CONTEXT_HPP
