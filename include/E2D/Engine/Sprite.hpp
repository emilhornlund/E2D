/**
* Sprite.hpp
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

#ifndef E2D_ENGINE_SPRITE_HPP
#define E2D_ENGINE_SPRITE_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/NonCopyable.hpp>

#include <E2D/Engine/Renderable.hpp>

#include <memory>

/**
 * @brief Namespace for E2D
 */
namespace e2d
{
class Renderer; // Forward declaration of Renderer
class Texture;  // Forward declaration of Texture

/**
 * @class Sprite
 * @brief Represents a 2D graphical object.
 *
 * The Sprite class is a concrete implementation of the Renderable interface.
 * It represents a 2D graphical object that can be rendered on the screen.
 * Each Sprite object maintains a texture that defines its visual appearance.
 * Sprites have render priorities that determine their rendering order.
 */
class E2D_ENGINE_API Sprite final : public Renderable
{
public:
    /**
     * @brief Default constructor for Sprite.
     *
     * Constructs a Sprite object.
     */
    Sprite();

    /**
     * @brief Destructor for Sprite.
     *
     * Destroys the Sprite object, releasing its resources.
     */
    ~Sprite() final;

    /**
     * @brief Retrieves the texture of the sprite.
     *
     * Returns a shared pointer to the Texture object associated with the sprite.
     * This texture defines the visual appearance of the sprite.
     *
     * @return std::shared_ptr<Texture> Shared pointer to the sprite's texture.
     */
    std::shared_ptr<Texture> getTexture() const;

    /**
     * @brief Sets the texture of the sprite.
     *
     * Assigns a new texture to the sprite. The texture defines the sprite's
     * visual appearance.
     *
     * @param texture Shared pointer to the new Texture object.
     */
    void setTexture(const std::shared_ptr<Texture>& texture);

    /**
     * @brief Retrieves the render priority of the sprite.
     *
     * Returns an integer representing the render priority of the sprite.
     * Sprites with higher priority values are rendered later (on top of others).
     *
     * @return int The render priority of the sprite.
     */
    int getRenderPriority() const final;

    /**
     * @brief Renders the sprite using the provided renderer.
     *
     * Renders the sprite using the given Renderer object. The method
     * uses the Renderer to draw the sprite's texture on the screen.
     *
     * @param renderer The Renderer object used for rendering the sprite.
     */
    void render(const Renderer& renderer) const final;

private:
    std::shared_ptr<Texture> m_texture; //!< Pointer to the sprite's texture.

}; // class Sprite

} // namespace e2d

#endif //E2D_ENGINE_SPRITE_HPP
