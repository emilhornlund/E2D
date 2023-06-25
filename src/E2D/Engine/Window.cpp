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

#include <SDL.h>

#include <iostream>

e2d::Window::Window() = default;

e2d::Window::~Window() = default;

bool e2d::Window::create(const std::string& title)
{
    this->m_window = WindowPtr(
        SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN));

    if (this->m_window == nullptr)
    {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        return false;
    }

    this->m_renderer = RendererPtr(SDL_CreateRenderer(this->m_window.get(), -1, SDL_RENDERER_ACCELERATED));
    if (this->m_renderer == nullptr)
    {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void e2d::Window::close()
{
    this->m_renderer.reset();
    this->m_window.reset();
}

void e2d::Window::display()
{
    SDL_RenderPresent(this->m_renderer.get());
}

void e2d::Window::clear(const e2d::Color& color)
{
    SDL_SetRenderDrawColor(this->m_renderer.get(), color.r, color.g, color.b, color.a);
    SDL_RenderClear(this->m_renderer.get());
}

[[maybe_unused]] bool e2d::Window::isOpened() const
{
    return (this->m_window != nullptr);
}

void SDLDestroyer::operator()(SDL_Window* window) const
{
    SDL_DestroyWindow(window);
}

void SDLDestroyer::operator()(SDL_Renderer* renderer) const
{
    SDL_DestroyRenderer(renderer);
}
