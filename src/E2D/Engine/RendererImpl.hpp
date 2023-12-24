/**
* RendererImpl.hpp
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

#ifndef E2D_ENGINE_RENDERER_IMPL_HPP
#define E2D_ENGINE_RENDERER_IMPL_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/Color.hpp>
#include <E2D/Core/NonCopyable.hpp>

#include <memory>

struct SDL_Renderer; // Forward declaration of SDL_Renderer
struct SDL_Window;   // Forward declaration of SDL_Window

/**
 * @brief Namespace for E2D internal
 */
namespace e2d::internal
{

/**
 * @class RendererImpl
 * @brief Internal implementation class for Renderer.
 *
 * This class is responsible for the low-level details of rendering operations.
 * It interfaces directly with the graphics hardware through the underlying rendering system.
 */
class E2D_ENGINE_API RendererImpl final : NonCopyable
{
public:
    /**
     * @brief Default constructor for RendererImpl.
     *
     * Initializes a new instance of the RendererImpl class.
     */
    RendererImpl();

    /**
     * @brief Destructor for RendererImpl.
     *
     * Cleans up resources used by the RendererImpl object.
     */
    ~RendererImpl();

    /**
     * @brief Initializes the renderer with the specified window.
     *
     * @param window A pointer to an SDL_Window object representing the window to render to.
     * @return True if the renderer is successfully created, false otherwise.
     */
    bool create(SDL_Window* window);

    /**
     * @brief Checks if the renderer is created and valid.
     *
     * @return True if the renderer is created, false otherwise.
     */
    [[maybe_unused]] bool isCreated() const;

    /**
     * @brief Destroys the renderer, freeing associated resources.
     */
    void destroy();

    /**
     * @brief Retrieves the native renderer object.
     *
     * @return A pointer to the underlying SDL_Renderer object.
     */
    SDL_Renderer* getRenderer() const;

    /**
     * @brief Executes the rendering process using a specified color.
     *
     * @param drawColor The color used for clearing the screen before rendering.
     */
    void render(const Color& drawColor) const;

private:
    SDL_Renderer* m_renderer{nullptr}; //!< Pointer to the SDL_Renderer object.

}; // class RendererImpl

} // namespace e2d::internal

#endif //E2D_ENGINE_RENDERER_IMPL_HPP
