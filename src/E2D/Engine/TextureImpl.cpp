/**
* TextureImpl.cpp
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

#include <E2D/Engine/TextureImpl.hpp>

// NOLINTBEGIN
#include <cstring> //unused, but must be included before SDL on macOS (bug?)
// NOLINTEND

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>

e2d::internal::TextureImpl::TextureImpl() = default;

e2d::internal::TextureImpl::~TextureImpl()
{
    this->destroy();
}

bool e2d::internal::TextureImpl::loadTexture(SDL_Renderer* renderer, const char* file)
{
    this->m_texture = IMG_LoadTexture(renderer, file);
    if (this->m_texture == nullptr)
    {
        std::cerr << "Failed to load texture: " << SDL_GetError() << '\n';
        return false;
    }
    if (SDL_QueryTexture(this->m_texture, nullptr, nullptr, &this->m_textureSize.x, &this->m_textureSize.y) != 0)
    {
        std::cerr << "Failed to query texture: " << SDL_GetError() << '\n';
        this->destroy();
        return false;
    }
    return true;
}

bool e2d::internal::TextureImpl::isLoaded() const
{
    return this->m_texture != nullptr;
}

void e2d::internal::TextureImpl::destroy()
{
    if (this->m_texture)
    {
        SDL_DestroyTexture(this->m_texture);
        this->m_texture     = nullptr;
        this->m_textureSize = {0, 0};
    }
}

const e2d::Vector2i& e2d::internal::TextureImpl::getSize() const
{
    return this->m_textureSize;
}

SDL_Texture* e2d::internal::TextureImpl::getTexture() const
{
    return this->m_texture;
}
