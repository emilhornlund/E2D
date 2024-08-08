/**
 * @file Text.hpp
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

#ifndef E2D_ENGINE_TEXT_HPP
#define E2D_ENGINE_TEXT_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/Rect.hpp>
#include <E2D/Core/Vector2.hpp>

#include <E2D/Engine/Object.hpp>
#include <E2D/Engine/Renderable.hpp>
#include <E2D/Engine/Transformable.hpp>

#include <memory>

namespace e2d
{

class Font; // Forward declaration of Font

namespace internal
{
class TextImpl; // Forward declaration of TextImpl
}

/**
 * @class Text
 * @ingroup engine
 * @brief Represents a text entity that can be transformed and rendered on the screen.
 *
 * The Text class provides functionalities to display and manage text rendered on the screen.
 * It supports setting the text string, font, and font size, and handles the transformations
 * and rendering of the text.
 */
class E2D_ENGINE_API Text : public Object, public Transformable, public Renderable
{
public:
    /**
     * @brief Constructs a new Text object.
     *
     * Initializes a new instance of the Text class.
     */
    Text();

    /**
     * @brief Constructs a new Text object with a specific identifier.
     *
     * Initializes a new instance of the Text class with the specified unique identifier.
     *
     * @param identifier A string representing the unique identifier of the text.
     */
    explicit Text(const std::string& identifier);

    /**
     * @brief Destructor.
     *
     * Ensures proper cleanup of resources upon destruction.
     */
    ~Text() override;

    /**
     * @brief Gets the current text string.
     *
     * Retrieves the current text string to be displayed.
     *
     * @return The current text string.
     */
    const std::string& getString() const;

    /**
     * @brief Sets the text string to be displayed.
     *
     * Updates the text string to be displayed by this Text object.
     *
     * @param string The new text string.
     */
    void setString(const std::string& string);

    /**
     * @brief Gets the font size.
     *
     * Retrieves the current font size used for rendering the text.
     *
     * @return The font size.
     */
    unsigned int getFontSize() const;

    /**
     * @brief Sets the font size.
     *
     * Updates the font size used for rendering the text.
     *
     * @param fontSize The new font size.
     */
    void setFontSize(unsigned int fontSize);

    /**
     * @brief Gets the font used for rendering the text.
     *
     * Retrieves a shared pointer to the Font object used for rendering the text.
     *
     * @return A shared pointer to the font.
     */
    const std::shared_ptr<const Font>& getFont() const;

    /**
     * @brief Sets the font used for rendering the text.
     *
     * Assigns a new font to be used for rendering the text.
     *
     * @param font A shared pointer to the new font.
     */
    void setFont(const std::shared_ptr<const Font>& font);

    /**
     * @brief Gets the size of the text entity.
     *
     * Retrieves the size of the text entity.
     *
     * @return Size of the text entity.
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
     * @brief Renders the text using the provided renderer.
     *
     * Renders the text to the screen using the specified Renderer object.
     *
     * @param renderer The Renderer object used for rendering the text.
     */
    void render(const e2d::Renderer& renderer) const final;

private:
    /**
     * @brief Updates the native texture of the text.
     *
     * Internal method to update the native texture when the text string, font,
     * or font size changes.
     */
    void updateNativeTexture();

    std::string                         m_string;       //!< The string of text to render.
    unsigned int                        m_fontSize{16}; //!< The size of the font.
    std::shared_ptr<const Font>         m_font;         //!< Pointer to the font used for rendering the text.
    std::unique_ptr<internal::TextImpl> m_textImpl;     //!< Pointer to the text implementation.

}; // Text class

} // namespace e2d

#endif //E2D_ENGINE_TEXT_HPP
