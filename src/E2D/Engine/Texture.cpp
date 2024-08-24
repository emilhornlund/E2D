/**
 * @file Texture.cpp
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

#include <E2D/Engine/Application.hpp>
#include <E2D/Engine/Renderer.hpp>
#include <E2D/Engine/Texture.hpp>
#include <E2D/Engine/TextureImpl.hpp>

#include <stdexcept>

e2d::Texture::Texture() : m_textureImpl(std::make_unique<internal::TextureImpl>())
{
    log::debug("Constructing Texture");
}

e2d::Texture::~Texture()
{
    log::debug("Destructing Texture");
}

bool e2d::Texture::loadFromFile(const std::string& filepath)
{
    return this->m_textureImpl->loadTexture(filepath.c_str());
}

bool e2d::Texture::loadFromMemory(const void* data, std::size_t size)
{
    return this->m_textureImpl->loadFromMemory(data, size);
}

bool e2d::Texture::isLoaded() const
{
    return this->m_textureImpl->isLoaded();
}

void e2d::Texture::destroy()
{
    this->m_textureImpl->destroy();
}

const e2d::Vector2i& e2d::Texture::getSize() const
{
    return this->m_textureImpl->getSize();
}

void* e2d::Texture::getNativeTextureHandle() const
{
    return this->m_textureImpl->getTexture();
}
