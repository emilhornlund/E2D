/**
 * Text.cpp
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

#include <E2D/Core/Rect.hpp>

#include <E2D/Engine/Application.hpp>
#include <E2D/Engine/Font.hpp>
#include <E2D/Engine/Renderer.hpp>
#include <E2D/Engine/SDLRenderUtils.hpp>
#include <E2D/Engine/Text.hpp>
#include <E2D/Engine/TextImpl.hpp>

#include <SDL.h>

e2d::Text::Text(const std::string& identifier) :
Entity(identifier),
m_font(nullptr),
m_textImpl(std::make_unique<internal::TextImpl>())
{
}

e2d::Text::~Text() = default;

const std::string& e2d::Text::getString() const
{
    return this->m_string;
}

void e2d::Text::setString(const std::string& string)
{
    this->m_string = string;
    this->updateNativeTexture();
}

unsigned int e2d::Text::getFontSize() const
{
    return this->m_fontSize;
}

void e2d::Text::setFontSize(unsigned int fontSize)
{
    this->m_fontSize = fontSize;
    this->updateNativeTexture();
}

const std::shared_ptr<const e2d::Font>& e2d::Text::getFont() const
{
    return this->m_font;
}

void e2d::Text::setFont(const std::shared_ptr<const Font>& font)
{
    this->m_font = font;
    this->updateNativeTexture();
}

const e2d::Vector2f& e2d::Text::getPosition() const
{
    return this->m_position;
}

void e2d::Text::setPosition(const e2d::Vector2f& position)
{
    this->m_position = position;
}

const e2d::Vector2f& e2d::Text::getOrigin() const
{
    return this->m_origin;
}

void e2d::Text::setOrigin(const e2d::Vector2f& origin)
{
    this->m_origin = origin;
}

const e2d::Vector2f& e2d::Text::getScale() const
{
    return this->m_scale;
}

void e2d::Text::setScale(const e2d::Vector2f& scale)
{
    this->m_scale = scale;
}

double e2d::Text::getRotation() const
{
    return this->m_rotation;
}

void e2d::Text::setRotation(double angle)
{
    this->m_rotation = angle;
}

e2d::FloatRect e2d::Text::getLocalBounds() const
{
    const auto destinationRectangle = internal::calculateSDLDestinationRect({{0, 0}, this->m_textImpl->getSize()},
                                                                            this->m_position,
                                                                            this->m_origin,
                                                                            this->m_scale);
    return {{static_cast<float>(destinationRectangle.x), static_cast<float>(destinationRectangle.y)},
            {static_cast<float>(destinationRectangle.w), static_cast<float>(destinationRectangle.h)}};
}

e2d::FloatRect e2d::Text::getGlobalBounds() const
{
    const auto destinationRectangle = internal::calculateSDLDestinationRect({{0, 0}, this->m_textImpl->getSize()},
                                                                            this->m_position,
                                                                            this->m_origin,
                                                                            this->m_scale);
    return {{static_cast<float>(destinationRectangle.x), static_cast<float>(destinationRectangle.y)},
            {static_cast<float>(destinationRectangle.w), static_cast<float>(destinationRectangle.h)}};
}

void e2d::Text::fixedUpdate()
{
}

void e2d::Text::variableUpdate(double deltaTime)
{
    (void)deltaTime;
}

int e2d::Text::getRenderPriority() const
{
    return 0;
}

void e2d::Text::render(const e2d::Renderer& renderer) const
{
    auto* texture = this->m_textImpl->getTexture();
    if (texture)
    {
        const IntRect textureRectangle({0, 0}, this->m_textImpl->getSize());

        const auto destinationRectangle = internal::calculateSDLDestinationRect(textureRectangle,
                                                                                this->m_position,
                                                                                this->m_origin,
                                                                                this->m_scale);

        const auto rotationPoint = internal::calculateSDLRotationPoint(this->m_textImpl->getSize(), this->m_origin, this->m_scale);

        const auto flip = internal::toSDLRendererFlip(this->m_scale);

        SDL_RenderCopyEx(static_cast<SDL_Renderer*>(renderer.getNativeRendererHandle()),
                         texture,
                         nullptr,
                         &destinationRectangle,
                         this->m_rotation,
                         &rotationPoint,
                         flip);
    }
}

void e2d::Text::updateNativeTexture()
{
    auto* renderer = static_cast<SDL_Renderer*>(this->getApplication().getRenderer().getNativeRendererHandle());
    auto* font     = static_cast<TTF_Font*>(this->m_font->getNativeFontHandle(this->m_fontSize));
    this->m_textImpl->updateNativeTexture(renderer, font, this->m_string);
}
