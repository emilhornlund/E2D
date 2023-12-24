/**
 * Application.cpp
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

#include <E2D/Core/Timer.hpp>

#include <E2D/Engine/Application.hpp>
#include <E2D/Engine/GraphicsSystem.hpp>
#include <E2D/Engine/Renderer.hpp>
#include <E2D/Engine/SystemManager.hpp>
#include <E2D/Engine/TextRenderingSystem.hpp>
#include <E2D/Engine/Window.hpp>

#include <SDL.h>

#include <iostream>
#include <utility>

e2d::Application::Application(std::string windowTitle) :
m_windowTitle(std::move(windowTitle)),
m_window(std::make_unique<Window>()),
m_renderer(std::make_unique<Renderer>()),
m_backgroundColor(Color::Black)
{
}

e2d::Application::~Application() = default;

int e2d::Application::run()
{
    SystemManager::getInstance().addSystem<GraphicsSystem>();
    SystemManager::getInstance().addSystem<TextRenderingSystem>();
    if (!SystemManager::getInstance().initializeAll())
    {
        return -1;
    }
    if (!this->m_window->create(this->m_windowTitle.c_str(), 800, 600))
    {
        return -1;
    }
    if (!this->m_renderer->create(*this->m_window))
    {
        return -1;
    }

    Timer        targetFrameTimer;
    double const targetFrameTime = 1.0 / 60.0;

    double elapsedTime = 0.0;
    double remainder   = 0.0;

    this->m_running = true;
    while (this->m_running)
    {
        targetFrameTimer.start();
        double elapsedFrameTimeAsSeconds = targetFrameTimer.getElapsedTimeAsSeconds();

        this->handleEvents();
        // TODO: Update game objects with a fixed frame rate of 1/60

        while (elapsedFrameTimeAsSeconds < targetFrameTime - remainder)
        {
            elapsedFrameTimeAsSeconds = targetFrameTimer.getElapsedTimeAsSeconds();
        }

        remainder = elapsedFrameTimeAsSeconds - (targetFrameTime - remainder);
        if (remainder >= targetFrameTime)
        {
            remainder = 0.0;
        }

        this->render();

        elapsedTime += elapsedFrameTimeAsSeconds;
        if (elapsedTime >= 1.0)
        {
            elapsedTime = 0.0;
        }
    }

    this->m_window->destroy();
    this->m_renderer->destroy();

    SystemManager::getInstance().shutdownAll();

    return this->m_exitCode;
}

[[maybe_unused]] bool e2d::Application::isRunning() const
{
    return this->m_running;
}

void e2d::Application::quit(int exitCode)
{
    this->m_exitCode = exitCode;
    this->m_running  = false;
}

void e2d::Application::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            this->quit();
        }
    }
}

void e2d::Application::render()
{
    this->m_renderer->render(this->m_backgroundColor);
}

const e2d::Color& e2d::Application::getBackgroundColor() const
{
    return this->m_backgroundColor;
}

void e2d::Application::setBackgroundColor(const e2d::Color& backgroundColor)
{
    this->m_backgroundColor = backgroundColor;
}
