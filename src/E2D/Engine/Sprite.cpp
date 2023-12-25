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
#include <E2D/Engine/Sprite.hpp>
#include <E2D/Engine/Texture.hpp>

#include <SDL.h>

e2d::Sprite::Sprite() = default;

e2d::Sprite::~Sprite() = default;

std::shared_ptr<e2d::Texture> e2d::Sprite::getTexture() const
{
    return this->m_texture;
}

void e2d::Sprite::setTexture(const std::shared_ptr<Texture>& texture)
{
    this->m_texture = texture;
}

int e2d::Sprite::getRenderPriority() const
{
    return 0;
}

void e2d::Sprite::render(const e2d::Renderer& renderer) const
{
    if (this->m_texture)
    {
        SDL_RenderCopy(static_cast<SDL_Renderer*>(renderer.getNativeRendererHandle()),
                       static_cast<SDL_Texture*>(this->m_texture->getNativeTextureHandle()),
                       nullptr,
                       nullptr);
    }
}
