/**
 * SDLRenderUtils.cpp
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

#include <E2D/Engine/SDLRenderUtils.hpp>

#include <cmath>

SDL_Rect e2d::internal::calculateSDLDestinationRect(const e2d::IntRect&  textureRect,
                                                    const e2d::Vector2f& position,
                                                    const e2d::Vector2f& origin,
                                                    const e2d::Vector2f& scale)
{
    const auto scaledWidth  = static_cast<int>(static_cast<float>(textureRect.width) * std::abs(scale.x));
    const auto scaledHeight = static_cast<int>(static_cast<float>(textureRect.height) * std::abs(scale.y));

    int adjustedPosX = static_cast<int>(position.x - (origin.x * scale.x));
    int adjustedPosY = static_cast<int>(position.y - (origin.y * scale.y));

    // Adjust position for negative scaling
    if (scale.x < 0)
    {
        adjustedPosX -= scaledWidth;
    }
    if (scale.y < 0)
    {
        adjustedPosY -= scaledHeight;
    }

    return {adjustedPosX, adjustedPosY, scaledWidth, scaledHeight};
}

SDL_Point e2d::internal::calculateSDLRotationPoint(const e2d::Vector2i& size,
                                                   const e2d::Vector2f& origin,
                                                   const e2d::Vector2f& scale)
{
    int rotationPointX = static_cast<int>(origin.x * std::abs(scale.x));
    int rotationPointY = static_cast<int>(origin.y * std::abs(scale.y));

    // Adjust rotation point for negative scaling
    if (scale.x < 0)
    {
        rotationPointX = size.x - rotationPointX;
    }
    if (scale.y < 0)
    {
        rotationPointY = size.y - rotationPointY;
    }

    return {rotationPointX, rotationPointY};
}

SDL_RendererFlip e2d::internal::toSDLRendererFlip(const e2d::Vector2f& scale)
{
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (scale.x < 0)
    {
        flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_HORIZONTAL);
    }
    if (scale.y < 0)
    {
        flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_VERTICAL);
    }
    return flip;
}
