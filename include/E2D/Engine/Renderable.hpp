/**
 * Renderable.hpp
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

#ifndef E2D_ENGINE_RENDERABLE_HPP
#define E2D_ENGINE_RENDERABLE_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/NonCopyable.hpp>

/**
 * @brief Namespace for E2D
 */
namespace e2d
{
class Renderer; // Forward declaration of Renderer

/**
 * @class Renderable
 * @brief Abstract base class for renderable objects.
 *
 * This class provides an interface for all objects that can be rendered
 * using a Renderer. It declares a pure virtual render method that must
 * be implemented by all derived classes.
 */
class E2D_ENGINE_API Renderable : NonCopyable
{
public:
    /**
     * @brief Virtual destructor for Renderable.
     *
     * Ensures proper destruction of derived classes.
     */
    virtual ~Renderable() = 0;

    /**
     * @brief Gets the render priority of the object.
     *
     * Return a value indicating the rendering order of the object.
     * Objects with higher priority values should be rendered later (on top).
     *
     * @return int The render priority of the object.
     */
    int getRenderPriority() const;

    /**
     * @brief Sets the render priority of the object.
     *
     * Sets a value indicating the rendering order of the object.
     * Objects with higher priority values should be rendered later (on top).
     *
     * @param renderPriority Value indicating the rendering order of the object.
     */
    void setRenderPriority(int renderPriority);

    /**
     * @brief Renders the object using the given renderer.
     *
     * This is a pure virtual function that must be implemented by
     * all derived classes to define how they should be rendered.
     *
     * @param renderer The renderer to use for rendering.
     */
    virtual void render(const Renderer& renderer) const = 0;

private:
    int m_renderPriority{0}; //!< Indicates the rendering order of the object

}; // class Renderable

} // namespace e2d

#endif //E2D_ENGINE_RENDERABLE_HPP
