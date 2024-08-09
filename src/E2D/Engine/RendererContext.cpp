/**
 * @file RendererContext.cpp
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
#include <E2D/Engine/Window.hpp>

e2d::internal::RendererContext::RendererContext() :
m_window(std::make_unique<Window>()),
m_renderer(std::make_unique<Renderer>())
{
    log::debug("Constructing RendererContext");
}

e2d::internal::RendererContext::~RendererContext()
{
    log::debug("Destructing RendererContext");
}

e2d::internal::RendererContext& e2d::internal::RendererContext::getInstance()
{
    static RendererContext instance;
    return instance;
}

bool e2d::internal::RendererContext::isInitialized() const
{
    return this->m_window->isCreated() && this->m_renderer->isCreated();
}

bool e2d::internal::RendererContext::initialize()
{
    if (this->isInitialized())
    {
        return false;
    }

    if (!this->m_window->create("E2D", 800, 600))
    {
        log::error("Failed to create window");
        return false;
    }

    if (!this->m_renderer->create(*this->m_window))
    {
        log::error("Failed to create renderer");
        return false;
    }

    return true;
}

void e2d::internal::RendererContext::destroy()
{
    if (this->m_renderer)
    {
        this->m_renderer->destroy();
    }

    if (this->m_window)
    {
        this->m_window->destroy();
    }
}

e2d::Window& e2d::internal::RendererContext::getWindow() const
{
    return *this->m_window;
}

e2d::Renderer& e2d::internal::RendererContext::getRenderer() const
{
    return *this->m_renderer;
}
