/**
 * @file Sprite.hpp
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

#ifndef E2D_ENGINE_SPRITE_HPP
#define E2D_ENGINE_SPRITE_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/NonCopyable.hpp>
#include <E2D/Core/Rect.hpp>
#include <E2D/Core/Vector2.hpp>

#include <E2D/Engine/Object.hpp>
#include <E2D/Engine/Renderable.hpp>
#include <E2D/Engine/Transformable.hpp>

#include <memory>

namespace e2d
{
class Renderer; // Forward declaration of Renderer
class Texture;  // Forward declaration of Texture

/**
 * @class Sprite
 * @ingroup engine
 * @brief Represents a 2D graphical sprite entity that can be transformed and rendered on the screen.
 *
 * The Sprite class provides functionalities to set texture and texture rectangle for rendering a sprite.
 * It handles sprite transformations such as scaling, rotation, and flipping internally, providing
 * an intuitive interface for game development.
 */
class E2D_ENGINE_API Sprite : public Object, public Transformable, public Renderable
{
public:
    /**
     * @brief Constructs a new Sprite object.
     *
     * Initializes a new instance of the Sprite class.
     */
    Sprite();

    /**
     * @brief Constructs a new Sprite object with a specific identifier.
     *
     * Initializes a new instance of the Sprite class with the specified unique identifier.
     *
     * @param identifier A string representing the unique identifier of the sprite.
     */
    explicit Sprite(const std::string& identifier);

    /**
     * @brief Destructor.
     *
     * Ensures proper cleanup of resources upon destruction.
     */
    ~Sprite() override;

    /**
     * @brief Retrieves the texture of the sprite.
     *
     * Returns a shared pointer to the Texture object associated with the sprite.
     * This texture defines the visual appearance of the sprite. If no texture is set,
     * a null shared pointer is returned.
     *
     * @return Shared pointer to the sprite's texture or null if none is set.
     */
    std::shared_ptr<const e2d::Texture> getTexture() const;

    /**
     * @brief Sets the texture of the sprite.
     *
     * Assigns a new texture to the sprite. The texture defines the sprite's
     * visual appearance.
     *
     * @param texture Shared pointer to the new Texture object.
     */
    void setTexture(const std::shared_ptr<const Texture>& texture);

    /**
     * @brief Retrieves the texture rectangle of the sprite.
     *
     * Returns the portion of the texture that is used for rendering the sprite.
     * Useful for spritesheets where multiple sprites are on a single texture.
     *
     * @return The current texture rectangle as an IntRect object.
     */
    const IntRect& getTextureRect() const;

    /**
     * @brief Sets the texture rectangle of the sprite.
     *
     * This rectangle defines the portion of the texture to be used for rendering.
     * Useful for spritesheets where multiple sprites are on a single texture.
     *
     * @param rectangle The IntRect object representing the new texture rectangle.
     */
    void setTextureRect(const IntRect& rectangle);

    /**
     * @brief Gets the size of the sprite entity.
     *
     * Retrieves the size of the sprite entity.
     *
     * @return Size of the sprite entity.
     */
    Vector2f getSize() const final;

    /**
     * @brief Fixed update method for consistent, time-sensitive updates.
     *
     * This method is called at a consistent rate, typically 60 times per second,
     * and is used for updates where consistent timing is crucial. This is ideal
     * for physics updates, collision detection, and other time-sensitive operations
     * where a fixed time step is necessary to maintain consistent behavior.
     */
    void fixedUpdate() override;

    /**
     * @brief Variable update method for frame-dependent updates.
     *
     * This method is called as often as possible, typically every frame, and receives
     * the time elapsed since the last update as a parameter. Use this method for updates
     * that can vary with the frame rate, such as animations, general game logic, and
     * operations that are not time-sensitive. The deltaTime parameter helps in creating
     * frame rate independent behavior.
     *
     * @param deltaTime The time elapsed since the last variable update in seconds.
     */
    void variableUpdate(double deltaTime) override;

    /**
     * @brief Renders the sprite using the provided renderer and with the applied transformations.
     *
     * This function utilizes internal utilities to calculate the destination rectangle,
     * rotation point, and flip state based on the sprite's current properties like
     * position, scale, origin, and rotation. If the sprite has no texture set, it will
     * not be rendered.
     *
     * @param renderer The Renderer object used for rendering the sprite.
     */
    void render(const Renderer& renderer) const final;

private:
    std::shared_ptr<const Texture> m_texture; //!< Pointer to the sprite's texture. Used for rendering the sprite.
    IntRect m_textureRect; //!< The texture rectangle defining the area of the texture to be rendered.

}; // class Sprite

} // namespace e2d

#endif //E2D_ENGINE_SPRITE_HPP
