/**
 * Renderer.cpp
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

#include <E2D/Engine/Renderable.hpp>
#include <E2D/Engine/Renderer.hpp>
#include <E2D/Engine/RendererImpl.hpp>
#include <E2D/Engine/RenderQueue.hpp>
#include <E2D/Engine/Window.hpp>

e2d::Renderer::Renderer() :
m_rendererImpl(std::make_unique<internal::RendererImpl>()),
m_renderQueue(std::make_unique<internal::RenderQueue>())
{
    log::debug("Constructing Renderer");
}

e2d::Renderer::~Renderer()
{
    log::debug("Destructing Renderer");
}

bool e2d::Renderer::create(const e2d::Window& window)
{
    return this->m_rendererImpl->create(static_cast<SDL_Window*>(window.getNativeWindowHandle()));
}

bool e2d::Renderer::isCreated() const
{
    return this->m_rendererImpl->isCreated();
}

void e2d::Renderer::destroy()
{
    this->m_rendererImpl->destroy();
}

void e2d::Renderer::draw(const e2d::Renderable* renderable)
{
    this->m_renderQueue->push(renderable);
}

void e2d::Renderer::render(const e2d::Color& drawColor) const
{
    this->m_rendererImpl->clear(drawColor);

    while (!this->m_renderQueue->isEmpty())
    {
        const Renderable* renderable = this->m_renderQueue->pop();
        if (renderable)
        {
            renderable->render(*this);
        }
    }

    this->m_rendererImpl->display();
}

void* e2d::Renderer::getNativeRendererHandle() const
{
    return this->m_rendererImpl->getRenderer();
}
