/**
 * @file TextureImpl.cpp
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
#include <E2D/Engine/RendererContext.hpp>
#include <E2D/Engine/TextureImpl.hpp>

// NOLINTBEGIN
#include <cstring> //unused, but must be included before SDL on macOS (bug?)
// NOLINTEND

#include <SDL.h>
#include <SDL_image.h>

e2d::internal::TextureImpl::TextureImpl()
{
    log::debug("Constructing TextureImpl");
}

e2d::internal::TextureImpl::~TextureImpl()
{
    log::debug("Destructing TextureImpl");
    this->destroy();
}

bool e2d::internal::TextureImpl::loadTexture(const char* file)
{
    auto* renderer = static_cast<SDL_Renderer*>(
        internal::RendererContext::getInstance().getRenderer().getNativeRendererHandle());
    this->m_texture = IMG_LoadTexture(renderer, file);
    if (this->m_texture == nullptr)
    {
        log::error("Failed to load texture: {}", SDL_GetError());
        return false;
    }
    if (SDL_QueryTexture(this->m_texture, nullptr, nullptr, &this->m_textureSize.x, &this->m_textureSize.y) != 0)
    {
        log::error("Failed to query texture: '{}'. Destroying texture.", SDL_GetError());
        this->destroy();
        return false;
    }
    return true;
}

bool e2d::internal::TextureImpl::loadFromMemory(const void* data, std::size_t size)
{
    SDL_RWops* rw = SDL_RWFromConstMem(data, static_cast<int>(size));
    if (rw == nullptr)
    {
        log::error("Failed to load texture from memory: {}", SDL_GetError());
        return false;
    }

    auto* renderer = static_cast<SDL_Renderer*>(
        internal::RendererContext::getInstance().getRenderer().getNativeRendererHandle());
    this->m_texture = IMG_LoadTexture_RW(renderer, rw, 1);
    if (this->m_texture == nullptr)
    {
        log::error("Failed to load texture from memory: {}", IMG_GetError());
        SDL_RWclose(rw);
        return false;
    }

    if (SDL_QueryTexture(this->m_texture, nullptr, nullptr, &this->m_textureSize.x, &this->m_textureSize.y) != 0)
    {
        log::error("Failed to query texture: '{}'. Destroying texture.", SDL_GetError());
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
