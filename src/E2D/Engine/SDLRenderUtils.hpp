/**
 * @file SDLRenderUtils.hpp
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

#ifndef E2D_ENGINE_SDL_RENDER_UTILS_HPP
#define E2D_ENGINE_SDL_RENDER_UTILS_HPP

#include <E2D/Engine/Export.hpp>

#include <E2D/Core/Rect.hpp>

#include <SDL.h>

namespace e2d::internal
{

/**
 * @ingroup engine
 * @brief @internal Converts an E2D Rect object to an SDL_Rect object.
 *
 * Converts the given E2D Rect object to an SDL_Rect object for use with SDL rendering functions.
 *
 * @tparam T The type of the rectangle's components (usually int or float).
 * @param rectangle The E2D Rect object to convert.
 * @return An SDL_Rect object representing the same rectangle.
 */
template <typename T>
inline SDL_Rect toSDLRect(const e2d::Rect<T>& rectangle)
{
    return {static_cast<int>(rectangle.left),
            static_cast<int>(rectangle.top),
            static_cast<int>(rectangle.width),
            static_cast<int>(rectangle.height)};
}

/**
 * @ingroup engine
 * @brief @internal Calculates the destination rectangle for rendering a texture in SDL.
 *
 * Computes the destination rectangle for rendering a texture, based on the texture's source rectangle,
 * position, origin, and scale. This rectangle defines where and how the texture will be drawn on the screen.
 *
 * @param textureRect The texture rectangle (source rectangle).
 * @param position The position of the texture on the screen.
 * @param origin The point around which the texture is scaled and rotated.
 * @param scale The scaling factors applied to the texture.
 * @return An SDL_Rect representing the destination rectangle for rendering.
 */
E2D_ENGINE_API SDL_Rect calculateSDLDestinationRect(const e2d::IntRect&  textureRect,
                                                    const e2d::Vector2f& position,
                                                    const e2d::Vector2f& origin,
                                                    const e2d::Vector2f& scale);

/**
 * @ingroup engine
 * @brief @internal Calculates the rotation point for an SDL texture.
 *
 * Computes the rotation point for a texture, considering the texture's size, its origin, and scale.
 * This point is used for rotating the texture during rendering.
 *
 * @param size The size of the texture after scaling.
 * @param origin The original point around which the texture is scaled and rotated.
 * @param scale The scaling factors applied to the texture.
 * @return An SDL_Point representing the rotation point for the texture.
 */
E2D_ENGINE_API SDL_Point
    calculateSDLRotationPoint(const e2d::Vector2i& size, const e2d::Vector2f& origin, const e2d::Vector2f& scale);

/**
 * @ingroup engine
 * @brief @internal Determines the SDL_RendererFlip value based on the scale of the texture.
 *
 * Determines the appropriate SDL_RendererFlip value for flipping the texture horizontally and/or vertically
 * based on its scaling factors.
 *
 * @param scale The scaling factors applied to the texture.
 * @return An SDL_RendererFlip value representing the flip state.
 */
E2D_ENGINE_API SDL_RendererFlip toSDLRendererFlip(const e2d::Vector2f& scale);

} // namespace e2d::internal

#endif //E2D_ENGINE_SDL_RENDER_UTILS_HPP
