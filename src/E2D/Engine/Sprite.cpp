/**
 * @file Sprite.cpp
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

#include <E2D/Core/Logger.hpp>

#include <E2D/Engine/Renderer.hpp>
#include <E2D/Engine/SDLRenderUtils.hpp>
#include <E2D/Engine/Sprite.hpp>
#include <E2D/Engine/Texture.hpp>

#include <SDL.h>

e2d::Sprite::Sprite() : e2d::Transformable(), e2d::Renderable()
{
    log::debug("Constructing Sprite");
}

e2d::Sprite::Sprite(const std::string& identifier) : e2d::Object(identifier)
{
    log::debug("Constructing Sprite with identifier '{}'", identifier);
}

e2d::Sprite::~Sprite()
{
    log::debug("Destructing Sprite");
}

std::shared_ptr<const e2d::Texture> e2d::Sprite::getTexture() const
{
    return this->m_texture;
}

void e2d::Sprite::setTexture(const std::shared_ptr<const Texture>& texture)
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

e2d::Vector2f e2d::Sprite::getSize() const
{
    return {static_cast<float>(this->m_textureRect.getSize().x), static_cast<float>(this->m_textureRect.getSize().y)};
}

void e2d::Sprite::fixedUpdate()
{
}

void e2d::Sprite::variableUpdate(double deltaTime)
{
    (void)deltaTime;
}

void e2d::Sprite::render(const e2d::Renderer& renderer) const
{
    if (this->m_texture)
    {
        const auto sourceRectangle = internal::toSDLRect(this->m_textureRect);

        const auto destinationRectangle = internal::calculateSDLDestinationRect(this->m_textureRect,
                                                                                this->getPosition(),
                                                                                this->getOrigin(),
                                                                                this->getScale());

        const auto destinationSize = Vector2i{destinationRectangle.w, destinationRectangle.h};
        const auto rotationPoint = internal::calculateSDLRotationPoint(destinationSize, this->getOrigin(), this->getScale());

        const auto flip = internal::toSDLRendererFlip(this->getScale());

        SDL_RenderCopyEx(static_cast<SDL_Renderer*>(renderer.getNativeRendererHandle()),
                         static_cast<SDL_Texture*>(this->m_texture->getNativeTextureHandle()),
                         &sourceRectangle,
                         &destinationRectangle,
                         this->getRotation(),
                         &rotationPoint,
                         flip);
    }
}
