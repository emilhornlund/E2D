/**
 * TextImpl.cpp
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

#include <E2D/Engine/TextImpl.hpp>

#include <SDL.h>
#include <SDL_ttf.h>

e2d::internal::TextImpl::TextImpl()
{
    log::debug("Constructing TextImpl");
}

e2d::internal::TextImpl::~TextImpl()
{
    log::debug("Destructing TextImpl");
    this->destroy();
}

void e2d::internal::TextImpl::updateNativeTexture(SDL_Renderer* renderer, TTF_Font* font, const std::string& text)
{
    if (!font)
    {
        log::warn("Failed to update font texture. No font supplied.");
        return;
    }
    if (!renderer || text.empty())
    {
        log::warn("Failed to update font texture. No renderer or text is empty.");
        TTF_CloseFont(font);
        return;
    }

    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), SDL_Color{255, 255, 255, 255});
    if (surface)
    {
        this->m_texture = SDL_CreateTextureFromSurface(renderer, surface);

        if (SDL_QueryTexture(this->m_texture, nullptr, nullptr, &this->m_textureSize.x, &this->m_textureSize.y) != 0)
        {
            log::warn("Failed to query texture: '{}'. Destroying text.", SDL_GetError());
            this->destroy();
        }

        SDL_FreeSurface(surface);
    }

    TTF_CloseFont(font);
}

const e2d::Vector2i& e2d::internal::TextImpl::getSize() const
{
    return this->m_textureSize;
}

SDL_Texture* e2d::internal::TextImpl::getTexture() const
{
    return this->m_texture;
}

void e2d::internal::TextImpl::destroy()
{
    if (this->m_texture)
    {
        SDL_DestroyTexture(this->m_texture);
        this->m_texture     = nullptr;
        this->m_textureSize = {0, 0};
    }
}
