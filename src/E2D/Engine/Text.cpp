/**
 * Text.cpp
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
#include <E2D/Core/Rect.hpp>

#include <E2D/Engine/Application.hpp>
#include <E2D/Engine/Font.hpp>
#include <E2D/Engine/Renderer.hpp>
#include <E2D/Engine/SDLRenderUtils.hpp>
#include <E2D/Engine/Text.hpp>
#include <E2D/Engine/TextImpl.hpp>

#include <SDL.h>

e2d::Text::Text() : m_font(nullptr), m_textImpl(std::make_unique<internal::TextImpl>())
{
    log::debug("Constructing Text");
}

e2d::Text::Text(const std::string& identifier) :
Object(identifier),
m_font(nullptr),
m_textImpl(std::make_unique<internal::TextImpl>())
{
    log::debug("Constructing Text");
}

e2d::Text::~Text()
{
    log::debug("Destructing Text");
}

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

e2d::Vector2f e2d::Text::getSize() const
{
    return {static_cast<float>(this->m_textImpl->getSize().x), static_cast<float>(this->m_textImpl->getSize().y)};
}

void e2d::Text::fixedUpdate()
{
}

void e2d::Text::variableUpdate(double deltaTime)
{
    (void)deltaTime;
}

void e2d::Text::render(const e2d::Renderer& renderer) const
{
    auto* texture = this->m_textImpl->getTexture();
    if (texture)
    {
        const IntRect textureRectangle({0, 0}, this->m_textImpl->getSize());

        const auto destinationRectangle = internal::calculateSDLDestinationRect(textureRectangle,
                                                                                this->getPosition(),
                                                                                this->getOrigin(),
                                                                                this->getScale());

        const auto rotationPoint = internal::calculateSDLRotationPoint(this->m_textImpl->getSize(),
                                                                       this->getOrigin(),
                                                                       this->getScale());

        const auto flip = internal::toSDLRendererFlip(this->getScale());

        SDL_RenderCopyEx(static_cast<SDL_Renderer*>(renderer.getNativeRendererHandle()),
                         texture,
                         nullptr,
                         &destinationRectangle,
                         this->getRotation(),
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
