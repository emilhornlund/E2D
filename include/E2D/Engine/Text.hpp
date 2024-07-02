/**
 * Text.hpp
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

#ifndef E2D_ENGINE_TEXT_HPP
#define E2D_ENGINE_TEXT_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/Rect.hpp>
#include <E2D/Core/Vector2.hpp>

#include <E2D/Engine/Entity.hpp>

#include <memory>

/**
 * @brief Namespace for E2D
 */
namespace e2d
{

class Font; // Forward declaration of Font

namespace internal
{
class TextImpl; // Forward declaration of TextImpl
}

/**
 * @class Text
 * @brief Represents a text entity that can be rendered on the screen.
 */
class E2D_ENGINE_API Text : public Entity
{
public:
    /**
     * @brief Default constructor for Text.
     *
     * Constructs a Text object.
     *
     * @param identifier
     */
    explicit Text(const std::string& identifier);

    /**
     * @brief Destructor for Text.
     *
     * Destroys the Text object, releasing its resources.
     */
    ~Text() override;

    /**
     * @brief Gets the current text string.
     *
     * @return The current text string.
     */
    const std::string& getString() const;

    /**
     * @brief Sets the text string to be displayed.
     *
     * @param string The new text string.
     */
    void setString(const std::string& string);

    /**
     * @brief Gets the font size.
     *
     * @return The font size.
     */
    unsigned int getFontSize() const;

    /**
     * @brief Sets the font size.
     *
     * @param fontSize The new font size.
     */
    void setFontSize(unsigned int fontSize);

    /**
     * @brief Gets the font used for rendering the text.
     *
     * @return A shared pointer to the font.
     */
    const std::shared_ptr<const Font>& getFont() const;

    /**
     * @brief Sets the font used for rendering the text.
     *
     * @param font A shared pointer to the new font.
     */
    void setFont(const std::shared_ptr<const Font>& font);

    /**
     * @brief Retrieves the current position of the text.
     *
     * @return The current position as a Vector2f object.
     */
    const Vector2f& getPosition() const;

    /**
     * @brief Sets the position of the text.
     *
     * This position represents the location of the text's origin in the world or screen space.
     *
     * @param position The Vector2f object representing the new position.
     */
    void setPosition(const Vector2f& position);

    /**
     * @brief Retrieves the origin point of the text.
     *
     * @return The current origin as a Vector2f object.
     */
    const Vector2f& getOrigin() const;

    /**
     * @brief Sets the origin point of the text.
     *
     * The origin is used as a pivot for transformations such as scaling and rotation.
     * Setting the origin to the center, for example, will rotate and scale the text around its center.
     *
     * @param origin The Vector2f object representing the new origin.
     */
    void setOrigin(const Vector2f& origin);

    /**
     * @brief Retrieves the current scaling factors of the text.
     *
     * @return The current scale as a Vector2f object.
     */
    const Vector2f& getScale() const;

    /**
     * @brief Sets the scaling factors of the text.
     *
     * Negative scaling factors will flip the text horizontally or vertically.
     *
     * @param scale The Vector2f object representing the new scaling factors.
     */
    void setScale(const Vector2f& scale);

    /**
     * @brief Retrieves the current rotation angle of the text in degrees.
     *
     * @return The current rotation angle.
     */
    double getRotation() const;

    /**
     * @brief Sets the rotation angle of the text.
     *
     * @param angle The new rotation angle in degrees.
     */
    void setRotation(double angle);

    /**
     * @brief Get the local bounding rectangle of the entity.
     *
     * @return Local bounding rectangle of the entity
     */
    FloatRect getLocalBounds() const;

    /**
     * @brief Get the global bounding rectangle of the entity.
     *
     * @return Global bounding rectangle of the entity
     */
    FloatRect getGlobalBounds() const;

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
     * @brief Retrieves the render priority of the text.
     *
     * Returns an integer representing the render priority of the text.
     * Sprites with higher priority values are rendered later (on top of others).
     *
     * @return int The render priority of the text.
     */
    int getRenderPriority() const override;

    /**
     * @brief Renders the text using the provided renderer.
     *
     * @param renderer The Renderer object used for rendering the text.
     */
    void render(const e2d::Renderer& renderer) const final;

private:
    /**
     * @brief
     */
    void updateNativeTexture();

    std::string                         m_string;       //!< The string of text to render.
    unsigned int                        m_fontSize{16}; //!< The size of the font.
    std::shared_ptr<const Font>         m_font;         //!< Pointer to the font used for rendering the text.
    std::unique_ptr<internal::TextImpl> m_textImpl;     //!< Pointer to the text implementation.
    Vector2f                            m_position;     //!< The position of the text in the world or screen space.
    Vector2f m_origin;      //!< The origin point of the text, used as a pivot for transformations.
    Vector2f m_scale{1, 1}; //!< The scaling factors of the text in the x and y directions.
    double   m_rotation{0}; //!< The rotation angle of the text in degrees.

}; // Text class

} // namespace e2d

#endif //E2D_ENGINE_TEXT_HPP
