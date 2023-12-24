/**
* RendererImpl.cpp
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

#include <E2D/Engine/RendererImpl.hpp>

#include <SDL.h>

#include <iostream>

e2d::internal::RendererImpl::RendererImpl() = default;

e2d::internal::RendererImpl::~RendererImpl()
{
    this->destroy();
}

bool e2d::internal::RendererImpl::create(SDL_Window* window)
{
    this->m_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (this->m_renderer == nullptr)
    {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << '\n';
        return false;
    }
    return true;
}

bool e2d::internal::RendererImpl::isCreated() const
{
    return this->m_renderer != nullptr;
}


void e2d::internal::RendererImpl::destroy()
{
    if (this->m_renderer)
    {
        SDL_DestroyRenderer(this->m_renderer);
        this->m_renderer = nullptr;
    }
}

SDL_Renderer* e2d::internal::RendererImpl::getRenderer() const
{
    return this->m_renderer;
}

void e2d::internal::RendererImpl::render(const e2d::Color& drawColor) const
{
    SDL_SetRenderDrawColor(this->m_renderer, drawColor.r, drawColor.g, drawColor.b, drawColor.a);
    SDL_RenderClear(this->m_renderer);
    SDL_RenderPresent(this->m_renderer);
}
