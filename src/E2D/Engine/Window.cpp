/**
 * Window.cpp
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

#include <E2D/Engine/Window.hpp>
#include <E2D/Engine/WindowImpl.hpp>

e2d::Window::Window() : m_windowImpl(std::make_unique<internal::WindowImpl>())
{
}

e2d::Window::~Window() = default;

bool e2d::Window::create(const char* title, int width, int height)
{
    return this->m_windowImpl->create(title, width, height);
}

bool e2d::Window::isCreated() const
{
    return this->m_windowImpl->isCreated();
}

void e2d::Window::destroy()
{
    this->m_windowImpl->destroy();
}

void* e2d::Window::getNativeWindowHandle() const
{
    return this->m_windowImpl->getWindow();
}
