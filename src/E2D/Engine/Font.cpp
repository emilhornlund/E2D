/**
 * @file Font.cpp
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

#include <E2D/Engine/Font.hpp>
#include <E2D/Engine/FontImpl.hpp>

e2d::Font::Font() : m_fontImpl(std::make_unique<internal::FontImpl>())
{
    log::debug("Constructing Font");
}

e2d::Font::~Font()
{
    log::debug("Destructing Font");
}

bool e2d::Font::loadFromFile(const std::string& filepath)
{
    return this->m_fontImpl->loadFromFile(filepath);
}

bool e2d::Font::loadFromMemory(const void* data, std::size_t size)
{
    return this->m_fontImpl->loadFromMemory(data, size);
}

void* e2d::Font::getNativeFontHandle(unsigned int fontSize) const
{
    return this->m_fontImpl->getFont(fontSize);
}
