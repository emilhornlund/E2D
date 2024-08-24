/**
 * @file Window.cpp
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

#include <E2D/Engine/Window.hpp>

#include <SDL.h>

e2d::internal::Window::Window()
{
    log::debug("Constructing Window");
}

e2d::internal::Window::~Window()
{
    log::debug("Destructing Window");
}

bool e2d::internal::Window::create(const char* title, int width, int height)
{
    log::debug("Creating window with title '{}', width '{}', and height '{}'", title, width, height);
    this->m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (this->m_window == nullptr)
    {
        log::error("Failed to create window: '{}'", SDL_GetError());
        return false;
    }
    return true;
}

bool e2d::internal::Window::isCreated() const
{
    return this->m_window != nullptr;
}

void e2d::internal::Window::destroy()
{
    if (this->m_window)
    {
        SDL_DestroyWindow(this->m_window);
        this->m_window = nullptr;
    }
}

SDL_Window* e2d::internal::Window::getNativeWindow() const
{
    return this->m_window;
}
