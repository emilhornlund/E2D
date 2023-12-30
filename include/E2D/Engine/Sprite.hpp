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
#include <E2D/Core/Rect.hpp>
#include <E2D/Core/Vector2.hpp>

#include <E2D/Engine/Entity.hpp>

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
 * The Sprite class provides functionalities to set texture, position, scale,
 * rotation, and texture rectangle for rendering a sprite. It handles sprite
 * transformations such as scaling, rotation, and flipping internally, providing
 * an intuitive interface for game development.
 */
class E2D_ENGINE_API Sprite : public Entity
{
public:
    /**
     * @brief Constructs a Sprite object with a specific identifier.
     *
     * @param identifier A string representing the unique identifier of the sprite.
     */
    explicit Sprite(const std::string& identifier);

    /**
     * @brief Destructor for Sprite.
     *
     * Destroys the Sprite object, releasing its resources.
     */
    ~Sprite() override = 0;

    /**
     * @brief Retrieves the texture of the sprite.
     *
     * Returns a shared pointer to the Texture object associated with the sprite.
     * This texture defines the visual appearance of the sprite. If no texture is set,
     * a null shared pointer is returned.
     *
     * @return std::shared_ptr<Texture> Shared pointer to the sprite's texture or null if none is set.
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
     * @brief Retrieves the texture rectangle of the sprite.
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
     * @brief Retrieves the current position of the sprite.
     *
     * @return The current position as a Vector2f object.
     */
    const Vector2f& getPosition() const;

    /**
     * @brief Sets the position of the sprite.
     *
     * This position represents the location of the sprite's origin in the world or screen space.
     *
     * @param position The Vector2f object representing the new position.
     */
    void setPosition(const Vector2f& position);

    /**
     * @brief Retrieves the origin point of the sprite.
     *
     * @return The current origin as a Vector2f object.
     */
    const Vector2f& getOrigin() const;

    /**
     * @brief Sets the origin point of the sprite.
     *
     * The origin is used as a pivot for transformations such as scaling and rotation.
     * Setting the origin to the center, for example, will rotate and scale the sprite around its center.
     *
     * @param origin The Vector2f object representing the new origin.
     */
    void setOrigin(const Vector2f& origin);

    /**
     * @brief Retrieves the current scaling factors of the sprite.
     *
     * @return The current scale as a Vector2f object.
     */
    const Vector2f& getScale() const;

    /**
     * @brief Sets the scaling factors of the sprite.
     *
     * Negative scaling factors will flip the sprite horizontally or vertically.
     *
     * @param scale The Vector2f object representing the new scaling factors.
     */
    void setScale(const Vector2f& scale);

    /**
     * @brief Retrieves the current rotation angle of the sprite in degrees.
     *
     * @return The current rotation angle.
     */
    double getRotation() const;

    /**
     * @brief Sets the rotation angle of the sprite.
     *
     * @param angle The new rotation angle in degrees.
     */
    void setRotation(double angle);

    /**
     * @brief Retrieves the render priority of the sprite.
     *
     * Returns an integer representing the render priority of the sprite.
     * Sprites with higher priority values are rendered later (on top of others).
     *
     * @return int The render priority of the sprite.
     */
    int getRenderPriority() const override = 0;

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
    std::shared_ptr<Texture> m_texture;     //!< Pointer to the sprite's texture. Used for rendering the sprite.
    IntRect                  m_textureRect; //!< The texture rectangle defining the area of the texture to be rendered.
    Vector2f                 m_position;    //!< The position of the sprite in the world or screen space.
    Vector2f                 m_origin;      //!< The origin point of the sprite, used as a pivot for transformations.
    Vector2f                 m_scale;       //!< The scaling factors of the sprite in the x and y directions.
    double                   m_rotation{0}; //!< The rotation angle of the sprite in degrees.

}; // class Sprite

} // namespace e2d

#endif //E2D_ENGINE_SPRITE_HPP
