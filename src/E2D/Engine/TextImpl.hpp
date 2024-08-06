/**
 * TextImpl.hpp
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

#ifndef E2D_ENGINE_TEXTIMPL_HPP
#define E2D_ENGINE_TEXTIMPL_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/NonCopyable.hpp>
#include <E2D/Core/Vector2.hpp>

#include <string>

struct SDL_Renderer;               // Forward declaration of SDL_Renderer
struct SDL_Texture;                // Forward declaration of SDL_Texture
using TTF_Font = struct _TTF_Font; // NOLINT(bugprone-reserved-identifier)

/**
 * @brief Namespace for E2D internal
 */
namespace e2d::internal
{

/**
 * @class TextImpl
 * @brief Internal implementation of the Text class, responsible for managing the rendering of text.
 */
class E2D_ENGINE_API TextImpl final : NonCopyable
{
public:
    /**
     * @brief Default constructor for TextImpl.
     *
     * Constructs a TextImpl object.
     */
    TextImpl();

    /**
     * @brief Destructor for TextImpl.
     *
     * Destroys the TextImpl object, releasing its resources.
     */
    ~TextImpl();

    /**
     * @brief Updates the native texture for the text.
     *
     * @param renderer The SDL renderer to use.
     * @param font The font to use for rendering the text.
     * @param text The text string to render.
     */
    void updateNativeTexture(SDL_Renderer* renderer, TTF_Font* font, const std::string& text);

    /**
     * @brief Retrieves the size of the internal SDL texture.
     *
     * This method returns the dimensions of the underlying SDL texture.
     * It queries the texture's width and height, storing them in a Vector2i.
     * If the texture is not loaded or the query fails, the method returns
     * a vector with zero values.
     *
     * @return const e2d::Vector2i& Reference to a Vector2i object representing the texture's size.
     */
    const e2d::Vector2i& getSize() const;

    /**
     * @brief Retrieves the native SDL texture object.
     *
     * @return Pointer to the underlying SDL_Texture object.
     */
    SDL_Texture* getTexture() const;

    /**
     * @brief Destroys the texture, freeing associated resources.
     */
    void destroy();

private:
    SDL_Texture*  m_texture{nullptr}; //!< Pointer to the SDL_Texture object.
    e2d::Vector2i m_textureSize;      //!< Stores the dimensions of the SDL_Texture object.

}; // TextImpl class

} // namespace e2d::internal

#endif //E2D_ENGINE_TEXTIMPL_HPP