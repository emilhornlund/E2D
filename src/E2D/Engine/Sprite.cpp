/**
* Sprite.cpp
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

#include <E2D/Engine/Renderer.hpp>
#include <E2D/Engine/SDLRenderUtils.hpp>
#include <E2D/Engine/Sprite.hpp>
#include <E2D/Engine/Texture.hpp>

#include <SDL.h>

e2d::Sprite::Sprite(const std::string& identifier) : e2d::Entity(identifier), m_scale({1, 1})
{
}

e2d::Sprite::~Sprite() = default;

std::shared_ptr<e2d::Texture> e2d::Sprite::getTexture() const
{
    return this->m_texture;
}

void e2d::Sprite::setTexture(const std::shared_ptr<Texture>& texture)
{
    this->m_texture = texture;
}

const e2d::IntRect& e2d::Sprite::getTextureRect() const
{
    return this->m_textureRect;
}

void e2d::Sprite::setTextureRect(const e2d::IntRect& rectangle)
{
    this->m_textureRect = rectangle;
}

const e2d::Vector2f& e2d::Sprite::getPosition() const
{
    return this->m_position;
}

void e2d::Sprite::setPosition(const e2d::Vector2f& position)
{
    this->m_position = position;
}

const e2d::Vector2f& e2d::Sprite::getOrigin() const
{
    return this->m_origin;
}

void e2d::Sprite::setOrigin(const e2d::Vector2f& origin)
{
    this->m_origin = origin;
}

const e2d::Vector2f& e2d::Sprite::getScale() const
{
    return this->m_scale;
}

void e2d::Sprite::setScale(const e2d::Vector2f& scale)
{
    this->m_scale = scale;
}

double e2d::Sprite::getRotation() const
{
    return this->m_rotation;
}

void e2d::Sprite::setRotation(double angle)
{
    this->m_rotation = angle;
}

void e2d::Sprite::render(const e2d::Renderer& renderer) const
{
    if (this->m_texture)
    {
        const auto sourceRectangle = internal::toSDLRect(this->m_textureRect);

        const auto destinationRectangle = internal::calculateSDLDestinationRect(this->m_textureRect,
                                                                                this->m_position,
                                                                                this->m_origin,
                                                                                this->m_scale);

        const auto destinationSize = Vector2i{destinationRectangle.w, destinationRectangle.h};
        const auto rotationPoint = internal::calculateSDLRotationPoint(destinationSize, this->m_origin, this->m_scale);

        const auto flip = internal::toSDLRendererFlip(this->m_scale);

        SDL_RenderCopyEx(static_cast<SDL_Renderer*>(renderer.getNativeRendererHandle()),
                         static_cast<SDL_Texture*>(this->m_texture->getNativeTextureHandle()),
                         &sourceRectangle,
                         &destinationRectangle,
                         this->m_rotation,
                         &rotationPoint,
                         flip);
    }
}
