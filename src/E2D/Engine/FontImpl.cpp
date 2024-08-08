/**
 * @file FontImpl.cpp
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

#include <E2D/Engine/FontImpl.hpp>

#include <SDL.h>
#include <SDL_ttf.h>

#include <fstream>
#include <iostream>

e2d::internal::FontImpl::FontImpl()
{
    log::debug("Constructing FontImpl");
}

e2d::internal::FontImpl::~FontImpl()
{
    log::debug("Destructing FontImpl");
}

bool e2d::internal::FontImpl::loadFromFile(const std::string& filepath)
{
    std::ifstream file(filepath, std::ios::binary | std::ios::ate);
    if (!file)
    {
        log::error("Failed to open font file '{}'", filepath);
        return false;
    }

    const auto size = file.tellg();
    file.seekg(0, std::ios::beg);

    this->m_fontData.resize(static_cast<size_t>(size));
    if (!file.read(reinterpret_cast<char*>(this->m_fontData.data()), size))
    {
        log::error("Failed to read font file '{}'", filepath);
        this->m_fontData.clear();
        return false;
    }

    return this->loadFromMemory(this->m_fontData.data(), this->m_fontData.size());
}

bool e2d::internal::FontImpl::loadFromMemory(const void* data, std::size_t size)
{
    this->m_fontData.assign(static_cast<const uint8_t*>(data), static_cast<const uint8_t*>(data) + size);
    return true;
}

TTF_Font* e2d::internal::FontImpl::getFont(unsigned int fontSize) const
{
    SDL_RWops* rw = SDL_RWFromConstMem(this->m_fontData.data(), static_cast<int>(this->m_fontData.size()));
    if (rw == nullptr)
    {
        log::error("Failed to load font from memory: '{}'", SDL_GetError());
        SDL_RWclose(rw);
        return nullptr;
    }

    auto* font = TTF_OpenFontRW(rw, 1, static_cast<int>(fontSize));
    if (!font)
    {
        log::error("Failed to load font from memory: '{}'", TTF_GetError());
        SDL_RWclose(rw);
        return nullptr;
    }

    return font;
}
